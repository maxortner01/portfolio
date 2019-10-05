#include "../headers/MainScene.h"

namespace gs
{
	void MainScene::create()
	{
		shader.loadFromFile("res/vertex.vert", age::Shader::VERTEX);
		shader.loadFromFile("res/frag.frag", age::Shader::FRAGMENT);
		shader.make();

		model = new age::Model(rawModel);
		model->rotate(age::Vec3f(3.14159f / 2.f, 0, 0));
		model->translate(age::Vec3f(0, -20.f, 0));
		model->setScale(age::Vec3f(1, 1, -1));
	}

	void MainScene::render(age::Event &event)
	{
		static int frame;
		using namespace age;

		// Camera movement
		{
			if (event.getKeyEvent().isKeyPressed(KeyEvent::ESCAPE))
			{
				Context::getCurrentContext().close();
			}

			float speed = .5f;
			if (event.getKeyEvent().isKeyDown(KeyEvent::L_SHIFT))
			{
				speed *= 2.f;
			}

			if (event.getKeyEvent().isKeyDown(KeyEvent::W))
			{
				camera.move(Camera::FORWARD, speed);
			}

			if (event.getKeyEvent().isKeyDown(KeyEvent::S))
			{
				camera.move(Camera::BACKWARD, speed);
			}

			if (event.getKeyEvent().isKeyDown(KeyEvent::A))
			{
				camera.move(Camera::LEFT, speed);
			}

			if (event.getKeyEvent().isKeyDown(KeyEvent::D))
			{
				camera.move(Camera::RIGHT, speed);
			}

			if (event.getKeyEvent().isKeyDown(KeyEvent::SPACE))
			{
				camera.translate({ 0, speed, 0 });
			}

			if (event.getKeyEvent().isKeyDown(KeyEvent::LCTRL))
			{
				camera.translate({ 0, -speed, 0 });
			}

			Vec2f mouse_delta = event.getMouse().getPosition() - Vec2f(Context::getCurrentContext().getSettings().width / 2.f, Context::getCurrentContext().getSettings().height / 2.f);

			camera.rotate({ mouse_delta.y / 300.f, -mouse_delta.x / 300.f, 0 });

			event.getMouse().setPosition({
				Context::getCurrentContext().getSettings().width / 2.f,
				Context::getCurrentContext().getSettings().height / 2.f
			});
		}

		clear(Color(200, 200, 200));

		if (function)
		{
			std::vector<age::VertexList3D> vs;

			function(vs, graph);

			for (int i = 0; i < vs.size(); i++)
			{
				// Passing vs to rawmodel causes memory leak <!-----------
				age::RawModel* raw = new age::RawModel(vs.at(i));
				age::Model* model  = new age::Model(raw);
			
				model->rotate(age::Vec3f(3.14159f / 2.f, 0, 0));
				model->translate(age::Vec3f(0, -20.f, 0));
				model->setScale(age::Vec3f(1, 1, -1));
			
				model->render(shader, camera);
			
				delete raw;
				delete model;
			}
		}

		model->render(shader, camera);

		frame++;
	}
}