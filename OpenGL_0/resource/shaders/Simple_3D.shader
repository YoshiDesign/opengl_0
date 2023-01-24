#shader vertex
#version 450

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 v_fragColor;
layout(location = 2) in vec3 normal;
layout(location = 3) in vec2 uv;

layout(location = 0) uniform mat4 projectionMatrix;
layout(location = 1) uniform mat4 viewMatrix;
layout(location = 2) uniform mat4 modelMatrix;

layout(location = 0) out vec3 f_fragColor;

void main() {
	vec4 positionWorld = modelMatrix * vec4(position, 1.0);	// Translate this vertex from model space to world space
	gl_Position = projectionMatrix * viewMatrix * positionWorld;
	f_fragColor = v_fragColor;
}

#shader fragment
#version 450
layout(location = 0) in vec3 fragColor;
layout(location = 0) out vec4 outColor;

void main() {
	outColor = vec4(fragColor, 1.0);
}