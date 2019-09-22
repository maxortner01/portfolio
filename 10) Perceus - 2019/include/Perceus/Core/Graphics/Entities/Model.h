#pragma once

#include "Perceus/Data/Transformable.h"
#include "Perceus/Data/Matrix.h"

#include "RawModel.h"

namespace pcs
{
class PERC_API Model : public Transformable3D<float>
    {
        RawModel* rawModel;
    public:
        Model(RawModel* rm);

        virtual void update(double deltaTime) { }

        Mat4f     getModelMatrix();
        RawModel* getRawModel() { return rawModel; }
    };
}