#include "../../../include/Ansel/Graphics/Shapes/Rectangle.h"
#include "../../../include/Ansel/Graphics/Shapes/VertexList.h"

#include <GL/glew.h>

namespace age
{
	void Rectangle::draw()
	{
		Vertex2D     vertex;
		vertex.color = getColor();

		VertexList2D rect;
		rect.setDrawType(Quads);

		vertex.position = {
			getGlobalLocation().x,
			getGlobalLocation().y
		};

		rect.addVertex(vertex);

		vertex.position = {
			getGlobalLocation().x + (getSize().x * getScale().x),
			getGlobalLocation().y
		};

		rect.addVertex(vertex);

		vertex.position = {
			getGlobalLocation().x + (getSize().x * getScale().x),
			getGlobalLocation().y + (getSize().y * getScale().y)
		};

		rect.addVertex(vertex);

		vertex.position = {
			getGlobalLocation().x,
			getGlobalLocation().y + (getSize().y * getScale().y)
		};

		rect.addVertex(vertex);

		rect.draw();
	}
}