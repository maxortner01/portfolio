#pragma once

#include "RenderAPI.h"

#include "Perceus/Data/Inc.h"

namespace pcs
{
namespace rend
{
    /**
     * @brief Enum that holds the types of APIs
     */
    enum RenderAPIType
    {
        OpenGL,
        DirectX11,
        Vulkan
    };

    /**
     * @brief Container for choosing various API types.
     */
    struct RenderSettings
    {
        RenderAPIType api = OpenGL;

        const char* getAPIName(RenderAPIType type) const
        {
			const char* r[]{
				"OpenGL",
				"DirectX11",
				"Vulkan"
			};

            return r[type];
        }
    };
    /**
     * @brief Class for retreiving the currently selected render API.
     */
    class PERC_API RenderObject
    {
    protected:
        /// Used for keeping track of the currently selected render API.
        static RenderSettings settings;

    public:
        /**
         * @brief Holds and retreives the currently selected render API interface.
         * 
         * @return RenderAPI* Currently selected render API interface.
         */
        static RenderAPI* rendAPI();
    };
}
}