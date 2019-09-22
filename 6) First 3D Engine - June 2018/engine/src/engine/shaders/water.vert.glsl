#version 440

in layout(location=0) vec3 vertices;

uniform mat4 matrix;

uniform float fog_start;
uniform float fog_distance;

out vec3 c;

void main() { 
    vec3 points = vec3(
        vertices.x, 
        sin(vertices.x) * .5,
        vertices.z
    );

	gl_Position = matrix * vec4(vertices.x, vertices.y, vertices.z, 1.0);

	c = vec3(0, 0, 1);

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