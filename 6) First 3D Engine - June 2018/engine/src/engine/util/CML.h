#ifndef CML_H_
#define CML_H_

#include <iostream>
#include <math.h>

namespace CML
{
    const float pi = std::acos(-1);
    enum MATenum {MAT_EMPTY, MAT_INDENTITY};

    /* ------- CONVERSIONS */
    float radians(float degrees);

    struct vert3f
    {
        float x, y, z;

        vert3f(float lx);
        vert3f(float lx, float ly);
        vert3f(float lx, float ly, float lz);

        inline void add(vert3f* amt) { x += amt->x; y += amt->y; z += amt->z; }
    };

    struct vert2f
    {
        float x, y;

        vert2f(float lx);
        vert2f(float lx, float ly);
    };

    class Matrix4f
    {
    public:
        float m[4][4];
        
        //Initialize float matrix pointer to 0 and preset
        Matrix4f();
        Matrix4f(CML::MATenum initval);
        
        void  init(CML::MATenum val);

        void  mult(int x, int y, float val);
        void  add(int x, int y, float val);
        void  set(int x, int y, float val);
        float get(int x, int y);

        Matrix4f* mul( Matrix4f* matrix );
        Matrix4f* mul( vert3f*   point  );

        //Translate matrix by translation
        void translate(vert3f* translation);
        void setTranslation(vert3f* translation);

        //Scale matrix by factor
        void scale(vert3f* factor);
        void setScale(vert3f* factor);

        //Rotate matrix by degrees
        void rotate(vert3f* rotation);

        //Return float matrix
        //float** getValues();
    };


}

#endif /* CML_H_ */