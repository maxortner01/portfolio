#include "model.h"

void Model::update() { /*...*/ }

Model::Model(std::vector<float> vertices, std::vector<float> colors) {
    outlines = false; draw_method = GL_STATIC_DRAW;
    
    std::cout << "\nCreating Model..." << std::endl;

    glCreateBuffers(2, buffers);
    std::cout << "  Vertex Buffer: " << buffers[VERTICES] << std::endl;

    newVertices(vertices, colors);
}

Model::Model(std::vector<float> vertices, std::vector<float> colors, int draw) {
    outlines = false; draw_method = draw;
    
    std::cout << "\nCreating Model..." << std::endl;

    glCreateBuffers(2, buffers);
    std::cout << "  Vertex Buffer: " << buffers[VERTICES] << std::endl;

    newVertices(vertices, colors);
}

void Model::newVertices(std::vector<float> vertices, std::vector<float> colors) {
    vertexData = vertices;

    std::cout << "  Binding buffer..." << std::endl;
    glBindBuffer(GL_ARRAY_BUFFER, buffers[VERTICES]);

    std::cout << "  Uploading data to buffer..." << std::endl;
    std::cout << "  " << vertices.size() << " vertices..." << std::endl; 
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], draw_method);
    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glDisableVertexAttribArray(0);
    
    std::cout << "  Done!" << std::endl;
}

void Model::render(Shader* shader, glm::mat4 model, Camera* camera) {

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //get perspective
    mat4 pers = camera->getProjection();
    //get view
    mat4 view = camera->getViewMatrix();
    //view * model
    mat4 modelview = view * model;
    //model * modelview
    mat4 target = pers * modelview;


    shader->bind();

    shader->setMatrix(target);
    shader->setUniform("fog_start", camera->getFogStart());
    shader->setUniform("fog_distance", camera->getFogDistance());

    glBindBuffer(GL_ARRAY_BUFFER, buffers[VERTICES]);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glDrawArrays(GL_TRIANGLES, 0, vertexData.size());

    if (outlines) {
        glDrawArrays(GL_LINES, 0, vertexData.size());
    }

    shader->unbind();
    glDisableVertexAttribArray(0);
}

void Model::toggleOutlines() {
    if (outlines) 
        outlines = false;
    else
        outlines = true;
}

Model::~Model() {
    glDeleteBuffers(2, buffers);    
}