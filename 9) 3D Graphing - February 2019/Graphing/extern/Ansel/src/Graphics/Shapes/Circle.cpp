#include "../../../include/Ansel/Graphics/Shapes/Circle.h"
#include "../../../include/Ansel/Graphics/Shapes/VertexList.h"

#define PI    3.14159
#define TWOPI 3.14159 * 2

namespace age
{
	void Circle::draw()
	{
		const float change = (float)TWOPI / (float)points;
		
		VertexList2D circle;
		circle.setDrawType(Triangles);

		for (int i = 0; i < points; i++)
		{
			const float x1 = getPosition().x + radius * cosf((float)i * change);
			const float y1 = getPosition().y + radius * sinf((float)i * change);

			const float x2 = getPosition().x + radius * cosf((float)(i + 1) * change);
			const float y2 = getPosition().y + radius * sinf((float)(i + 1) * change);

			Vertex2D p1, p2, p3;
			p1.position = { x1, y1 };
			p2.position = { x2, y2 };
			p3.position = getPosition();
			p1.color = getColor();
			p2.color = getColor();
			p3.color = getColor();

			circle.addVertex(p1);
			circle.addVertex(p2);
			circle.addVertex(p3);
		}

		circle.draw();
	}
}