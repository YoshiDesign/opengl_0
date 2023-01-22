#shader vertex
#version 450

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;
layout(location = 2) in vec3 normal;
layout(location = 3) in vec2 uv;
uniform mat4 u_MVP;

layout(location = 0) out vec3 fragColor;

void main() {
	gl_Position = u_MVP * vec4(position, 1.0);
	fragColor = color;
}

#shader fragment
#version 450

layout(location = 0) in vec3 fragColor;

layout(location = 0) out vec4 outColor;

void main() {
	outColor = vec4(gl_FragCoord);
}