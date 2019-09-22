#pragma once

#include "../Graphics/Graphics3D/Model.h"
#include "../Graphics/Graphics3D/RawModel.h"
#include "../Graphics/Graphics3D/Camera.h"
#include "../Graphics/Shader.h"
#include "Scene.h"

#include <vector>

namespace age
{
	class Scene3D : public Scene, public Target3D
	{
		std::vector<Model*> models;
		std::vector<RawModel*> rawModels;

	protected:
		Camera camera;
		Shader shader;

	public:
		enum 
		{
			TRIANGLES,
			POINTS,
			LINES
		} typedef RenderType;

		ANSEL_API Scene3D();
		virtual ~Scene3D() {}

		virtual void create()  {}
		virtual void destroy() {}

		ANSEL_API void renderObjects(age::Surface surface, RenderType type = TRIANGLES);
		ANSEL_API void renderObjects(RenderType type = TRIANGLES);
		ANSEL_API void clear(Color color = Color());

		void pushModel(Model* object)
		{
			models.push_back(object);
		}

		template<typename... Args>
		RawModel &makeRawModel(Args... args)
		{
			RawModel* rawModel = new RawModel(args...);
			rawModels.push_back(rawModel);
			return *rawModel;
		}
	};
}