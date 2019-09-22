#pragma once

#include "RawModelParser.h"

namespace pcs
{
    class ParserOBJ : public Util::RawModelParser
    {
    public:
        using Util::RawModelParser::RawModelParser;

        VertexArray* parseFile() const override;
    };
}