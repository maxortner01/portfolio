#include "CML.h"

using namespace CML;

float CML::radians(float degrees) {
    //return degrees;
    return degrees * (pi / 180.0f);
}

/* ------- VERTEX */
vert3f::vert3f(float lx)                     { x = lx; y = 0;  z = 0;  }
vert3f::vert3f(float lx, float ly)           { x = lx; y = ly; z = 0;  }
vert3f::vert3f(float lx, float ly, float lz) { x = lx; y = ly; z = lz; }

vert2f::vert2f(float lx)                     { x = lx; y = 0;  }
vert2f::vert2f(float lx, float ly)           { x = lx; y = ly; }
    
/* ------- MATRIX */
Matrix4f::Matrix4f() {
    init(MAT_INDENTITY);
}

Matrix4f::Matrix4f(MATenum initval) {
    init(initval);
}

void Matrix4f::init(MATenum val) {
    //Set all values to 0
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            m[y][x] = 0;
        }
    }

    //If chosen preset is identity
    if (val == MAT_INDENTITY) {
        m[0][0] = 1;
        m[1][1] = 1;
        m[2][2] = 1;
        m[3][3] = 1;
    }
}

void Matrix4f::mult(int x, int y, float val) {
    m[y][x] = m[y][x] * val;
}

void Matrix4f::add(int x, int y, float val) {
    m[y][x] = m[y][x] + val;
}

void Matrix4f::set(int x, int y, float val) {
    m[y][x] = val;
}

float Matrix4f::get(int x, int y) {
    return m[y][x];
}

Matrix4f* Matrix4f::mul(Matrix4f* matrix) {
    Matrix4f* target = new Matrix4f(MAT_INDENTITY);

    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            float val = 0.0f;

            for (int s = 0; s < 4; s++) {
                val += (m[s][x] * matrix->get(y, s));
            }

            target->set(x, y, val);
        }
    }

    return target;
}

Matrix4f* Matrix4f::mul(vert3f* point) {
    Matrix4f* target = new Matrix4f(MAT_INDENTITY);

    float positions[4] {point->x, point->y, point->z, 1};
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            target->set(x, y, m[y][x] * positions[x]);
        }
    }

    return target;
}
        
//Translate matrix by translation
void Matrix4f::translate(vert3f* translation) {
    add(3, 0, translation->x);
    add(3, 1, translation->y);
    add(3, 2, translation->z);
}

void Matrix4f::setTranslation(vert3f* translation) {
    set(3, 0, translation->x);
    set(3, 1, translation->y);
    set(3, 2, translation->z);
}

//Scale matrix by factor
void Matrix4f::scale(vert3f* factor) {
    add(0, 0, factor->x);
    add(1, 1, factor->y);
    add(2, 2, factor->z);
}

//Set scale
void Matrix4f::setScale(vert3f* factor) {
    set(0, 0, factor->x);
    set(1, 1, factor->y);
    set(2, 2, factor->z);
}

//Rotate matrix by degrees
void Matrix4f::rotate(vert3f* rotation) {
    vert3f* rr = new vert3f( 
        radians(rotation->x),
        radians(rotation->y),
        radians(rotation->z)
    );

    float m00 =   std::cos( rr->y )  * std::cos( rr->z );
    float m10 = -(std::cos( rr->y )) * std::sin( rr->z );
    float m20 =   std::sin( rr->y );
    
    float m01 =  ( std::sin( rr->x ) * std::sin( rr->y ) * std::cos( rr->z ) );
    /*-*/ m01 = m01 + ( std::cos( rr->x ) * std::sin( rr->z ) );
    float m11 = -( std::sin( rr->x ) ) * std::sin( rr->y ) * std::sin( rr->z );
    /*-*/ m11 = m11 + ( std::cos( rr->x ) * std::cos( rr->z ) );
    float m21 = -( std::sin( rr->x ) ) * std::cos( rr->y );

    float m02 = -( std::cos( rr->x ) ) * std::sin( rr->y ) * std::cos( rr->z );
    /*-*/ m02 = m02 + ( std::sin( rr->x ) * std::sin( rr->z ) );
    float m12 =  ( std::cos( rr->x ) * std::sin( rr->y ) * std::sin( rr->z ) );
    /*-*/ m12 = m12 + ( std::sin( rr->x ) * std::cos( rr->z ) );
    float m22 =  ( std::cos( rr->x ) * std::cos( rr->y ) );

    add( 0, 0, m00 );
    add( 1, 0, m10 );
    add( 2, 0, m20 );
   
    add( 0, 1, m01 );
    add( 1, 1, m11 );
    add( 2, 1, m21 );

    add( 0, 2, m02 );
    add( 1, 2, m12 );
    add( 2, 2, m22 );

    /*
    //rotate by x
    add(1, 1,      std::cos( rr->x ));
    add(2, 1, -1 * std::sin( rr->x ));
    add(1, 2,      std::sin( rr->x ));
    add(2, 2,      std::cos( rr->x ));

    //rotate by y
    add(0, 0,      std::cos( rr->y ));
    add(0, 2, -1 * std::sin( rr->y ));
    add(2, 0,      std::sin( rr->y ));
    add(2, 2,      std::cos( rr->y ));

    //rotate by z
    add(0, 0,      std::cos( rr->z ));
    add(1, 0, -1 * std::sin( rr->z ));
    add(0, 1,      std::sin( rr->z ));
    add(1, 1,      std::cos( rr->z ));
    */
    delete rr;
}

/*Return float matrix
float** Matrix4f::getValues() {
    return m;
} */