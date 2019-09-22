#version 440

in layout(location=0) vec3 vertices;
//in layout(location=1) vec3 color;

//in vec4 color;

//attribute vec3 vertices;

uniform mat4  matrix;
uniform float fog_start;
uniform float fog_distance;

out vec3  c;


void main() { 
	gl_Position = matrix * vec4(vertices.x, vertices.y, vertices.z, 1.0);

	vec3 color = vec3(.133, .545, .13);

	c = vec3(
		color.x / (vertices.y / 10.0), 
		color.y / (vertices.y / 10.0), 
		color.z / (vertices.y / 10.0)
	);

	if (vertices.y < .75) {
		c = vec3(.761, .698, .502);
	}

	if (vertices.y < 0) {
		float amt = -1 * vertices.y;
		c = vec3(.1 / amt, .25 / amt, .75 / amt);
	}

	float dist = sqrt(pow(gl_Position.x, 2) + pow(gl_Position.y, 2) + pow(gl_Position.z, 2));
	if (dist > fog_start) {
		float rel_dist = dist - fog_start;
		rel_dist = rel_dist / 2.0;

		if (rel_dist > fog_distance) {
			c = vec3(0, 0, 0);
		} else {
			vec3 co = vec3(c.x / rel_dist, c.y / rel_dist, c.z / rel_dist);

			/**/ if (co.x > c.x) { c.x = c.x; }
			else 				 { c.x = co.x; }
			
			/**/ if (co.y > c.y) { c.y = c.y; }
			else 				 { c.y = co.y; }
			
			/**/ if (co.z > c.z) { c.z = c.z; }
			else 				 { c.z = co.z; }
		}
	}
}