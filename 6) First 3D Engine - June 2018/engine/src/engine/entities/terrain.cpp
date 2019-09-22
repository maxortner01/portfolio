#include "terrain.h"

float distance(vec2 loc1, vec2 loc2) {
    return std::sqrt(std::pow(loc2.x - loc1.x, 2) + std::pow(loc2.y - loc1.y, 2));
}

/* <---------- STRUCT: TERRAIN ----------> */

Terrain::Sector::Sector(float x, float y, Shader* s, Shader* t, Shader* w, Camera* c) {
    shader = s; treeshader = t; watershader = w; camera = c;
    location = vec2(x * SECTOR_WIDTH, y * SECTOR_DEPTH);

    //std::thread generation(&generate, x, y);
    //generation.join();
    generate(x, y);
}

void Terrain::Sector::generate(float x, float z) {
    std::vector<float> vertices;
    std::vector<float> treevertices;
    std::vector<float> watervertices;

    x = x * SECTOR_WIDTH; z = z * SECTOR_DEPTH;

    for (int Z = 0; Z < SECTOR_DEPTH; Z++) {
        for (int X = 0; X < SECTOR_WIDTH; X++) {
            vec2 location = vec2(x + X, z + Z);

            //Get corner values from simplex noise function
            std::vector<float> corners = {
                Terrain::getval(location.x,     location.y + 1), 
                Terrain::getval(location.x + 1, location.y + 1),
                Terrain::getval(location.x,     location.y), 
                Terrain::getval(location.x + 1, location.y)
            };

            //Create tile vertices using corner values
            std::vector<float> tile = VERT::getTile(
                corners[0], corners[1], corners[2], corners[3]);

            //Transform current tile by position in sector
            for (int v = 0; v < tile.size() / 3; v++) {
                int index        = v * 3;
                tile[index]     += location.x;
                tile[index + 2] += location.y;

                vertices.push_back(tile[index]);
                vertices.push_back(tile[index + 1]);
                vertices.push_back(tile[index + 2]);
            }

            //Generate tree
            int val = rand() % 250;
            if (val < 5 && corners[2] > 1) {
                std::vector<float> tree = VERT::getCylinder(vec3(location.x, corners[2] - 1, location.y), 15, .25, (rand() % 3) + 6);

                for (int i = 0; i < tree.size(); i++) {
                    treevertices.push_back(tree[i]);
                }
            }

            //Generate water
            std::vector<float> waterTile = VERT::getTile(0, 0, 0, 0);

            //Transform current tile by position in sector
            for (int v = 0; v < tile.size() / 3; v++) {
                int index        = v * 3;
                waterTile[index]     += location.x;
                waterTile[index + 2] += location.y;

                watervertices.push_back(waterTile[index]);
                watervertices.push_back(waterTile[index + 1]);
                watervertices.push_back(waterTile[index + 2]);
            }

        }
    }

    model = new Model(vertices,      std::vector<float>{});
    trees = new Model(treevertices,  std::vector<float>{});
    water = new Model(watervertices, std::vector<float>{});
}

void Terrain::Sector::render() const {
    water->render(watershader, mat4(1.0), camera);
    model->render(shader,      mat4(1.0), camera);
    trees->render(treeshader,  mat4(1.0), camera);
}

Terrain::Sector::~Sector() {
    delete trees;
    delete model;
    delete water;
}

/* <---------- CLASS: TERRAIN ----------> */

float Terrain::getval(float x, float y) {
    float size = 800.0;

    //Simplex noise object
    SimplexNoise* simplex = new SimplexNoise();

    float simp         = simplex->fractal(6, x / (25.0 * size),  y / (25.0 * size))  * (45.0 * (size / 50));
    float simp2        = simplex->fractal(6, x / (120.0 * size),  y / (120.0 * size))  * (25.0 * (size / 50));
    float simp_small   = simplex->fractal(6, x / (15.0 * size),    y / (15.0 * size))   * (10.0 * (size / 50));
    float simp_smaller = simplex->fractal(6, x / (.25 * size),     y / (.25 * size))    * (3 * (size / 50));

    simp = (simp + simp2 + simp_small + simp_smaller) / 4.0;

    delete simplex;
    return simp;
}

Terrain::Terrain(Camera* camera) {
    currentCamera = camera;
    
    vec3 position = camera->transform->getPosition();
    vec2 location = getTileLocation(position.x, position.z);

    for (int z = 0; z < 3; z++) {
        for (int x = 0; x < 3; x++) {
            //Get position by offsetting by player's position and multiplying it by the sector size
            float pos_x = location.x + x - 1; float pos_z = location.y + z - 1;

            std::cout << "Creating sector... (" << pos_x << ", " << pos_z << ")" << std::endl;
            Sector* sector = new Sector(pos_x, pos_z, shader, treeshader, watershader, camera);
            sectors.push_back(sector);
        }
    }
}

void Terrain::render() {
    std::vector<Sector*> s;

     vec2 cameraPos = vec2(
        currentCamera->transform->getPosition().x,
        currentCamera->transform->getPosition().z
    ); 

    vec2 relativeCameraPos = getTileLocation(cameraPos.x, cameraPos.y);
    vec2 cameraSector      = getSectorLocation(cameraPos.x, cameraPos.y);

    std::vector<vec2> locations;

    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            locations.push_back(vec2( cameraSector.x + x - 1, cameraSector.y + y - 1 ));
        }
    }

    for (int i = 0; i < sectors.size(); i++) {
        Sector* sector = sectors[i];

        vec2  sectorPos = getSectorLocation(sector->location.x, sector->location.y);
        float dist = distance(cameraPos, sector->location);

        for (int j = 0; j < locations.size(); j++) {
            if (sectorPos == locations[j]) { locations.erase( locations.begin() + j ); }
        }

        //If distance is greater than 5 delete sector
        if (dist > SECTOR_WIDTH * 5) {
            delete sector;
            continue;
        }        

        //Otherwise add it to temporary list and render
        s.push_back(sector);
        sector->render();
    }

    //std::cout << "Locations: " << locations.size() << std::endl;

    for (int i = 0; i < locations.size(); i++) {
        Sector* sector = new Sector(locations[i].x, locations[i].y, shader, treeshader, watershader, currentCamera);
        s.push_back(sector);
    }

    //Make temporary list the main list
    sectors = s;
}

/*
void Terrain() {
    int width = 30; int height = 30;

    //Generate simplex array
    for (int y = 0; y < height + 10; y++) {
        std::vector<float> row;
        for (int x = 0; x < width + 10; x++) {
            row.push_back(getval(x, y));
        }
        simplexArray.push_back(row);
    }

    //Generate vertices from noise
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            std::vector<float> v = VERT::getTile(
                simplexArray[i + 1][j], 
                simplexArray[i + 1][j + 1],
                simplexArray[i][j], 
                simplexArray[i][j + 1]
            );
        
            for (int l = 0; l < v.size() / 3; l++) {
                int index = l * 3;
                v[index] += j;    //.25 seperation
                v[index + 2] += i;    //.25 seperation

                vertices.push_back(v[index]);
                vertices.push_back(v[index + 1]);
                vertices.push_back(v[index + 2]);
            }
        }
    }

    terrainModel = new Model(vertices, std::vector<float>{});

    genTrees();
}

void Terrain::render(Camera* camera) {
    //Model::render(vertices, shader, new vert3f(.133, .545, .13), glm::mat4(1.0), camera);
    terrainModel->render(shader, mat4(1.0), camera);
    //treeModel->render(treeShader, mat4(1.0), camera);
    //renderTrees(camera);
}
void Terrain::genTrees() {
    int width = 1000; int height = 1000;
    float seperation = 200.0;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            const float val = ((getval(x, y) + 1) / 2.0) / 60.0;
            const float ran = (rand() % 100) / 2.0;

            if (ran < val) {
                const int x_val = x + ((rand() % 50) / 10.0);
                const int y_val = y + ((rand() % 50) / 10.0);

                //if below water level, skip
                if (getval(x_val, y_val) < .75) {
                    continue;
                }

                std::vector<float> verts = VERT::getCylinder(new vert3f(
                    //LOCATION
                    x_val, 
                    getval(x_val, y_val), 
                    y_val

                ), 15, .37, ((rand() % 10) / 3) + 10);
                for (int i = 0; i < verts.size(); i++) {
                    treeVertices.push_back(verts[i]);
                }
            }
        }
    }

    std::cout << "Tree Vertices: " << treeVertices.size() << std::endl;
    treeModel = new Model(treeVertices, std::vector<float>{});
}

void Terrain::renderTrees(Camera* camera) {
    //Model::render(treeVertices, treeShader, new vert3f(.325, .192, .094), mat4(1.0), camera);
}
*/