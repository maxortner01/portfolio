#version 330 core

layout(location = 0) in vec3 vertex;
layout(location = 1) in vec4 color;
layout(location = 2) in vec3 normal;

layout(location = 3) in vec4 translation;
layout(location = 4) in vec4 rotation;
layout(location = 5) in vec4 scale;
layout(location = 6) in vec4 origin;

uniform mat4 projection;
uniform mat4 view;

out vec4 vertColor;

mat4 makeTransformMatrix(vec4 loc) {
	return mat4(
			1, 0, 0, loc.x,
			0, 1, 0, loc.y,
			0, 0, 1, loc.z,
			0, 0, 0, 1
		);
}

mat4 makeRotationMatrix(vec4 rot) {
	mat4 rot_x = mat4(
		1, 0, 		   0,		    0,
		0, cos(rot.x), -sin(rot.x), 0,
		0, sin(rot.x),  cos(rot.x), 0,
		0, 0,          0,           1
	);

	mat4 rot_y = mat4(
		 cos(rot.y), 0, sin(rot.y), 0,
		 0,			 1, 0, 		    0,
		-sin(rot.y), 0, cos(rot.y), 0,
		 0, 	     0, 0,          1
	);

	mat4 rot_z = mat4(
		cos(rot.z), -sin(rot.z), 0, 0,
		sin(rot.z),  cos(rot.z), 0, 0,
		0, 			 0, 		 1, 0,
		0, 			 0, 		 0, 1
	);

	return rot_x * rot_y * rot_z;
}

mat4 makeScaleMatrix(vec4 sc) {
	return mat4(
		sc.x, 0,    0,    0,
		0,    sc.y, 0,    0,
		0,    0,    sc.z, 0,
		0,    0,    0,    1
	);
}


mat4 makeModel(vec4 loc, vec4 rot, vec4 sc) {
	return makeScaleMatrix(sc) * makeRotationMatrix(rot) * makeTransformMatrix(loc);
}

void main()
{
	mat4 model = makeModel(translation, rotation, scale);
	
	vec3 realNormal = normalize(vec4(normal.xyz, 1.0) * makeScaleMatrix(scale) * makeRotationMatrix(rotation)).xyz;
	vertColor = color * max(dot(realNormal, vec3(0, 0, -1)), 0);
	vertColor.w = color.w;

	vertColor = color;
	
	vec4 position = vec4(
		vertex.x + origin.x,
		vertex.y + origin.y,
		vertex.z + origin.z,
		1.0
	);
	
	gl_Position = position * model * view * projection;
}