#include "Perceus/Core/Graphics/Entities/Model.h"

namespace pcs
{
    Model::Model(RawModel* rm) :
        rawModel(rm)
    {
        setScale({ 1, 1, 1 });
    }

    Mat4f Model::getModelMatrix()
    {
        Mat4f t = Mat4f::makeTranslation(getLocation());
        Mat4f r = Mat4f::makeRotation(getRotation());
        Mat4f s = Mat4f::makeScale(getScale());

        return s * t * r;
    }
}