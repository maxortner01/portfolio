#version 440

in vec3 c;

void main() {
	gl_FragColor = vec4(c.x, c.y, c.z, .25);
}