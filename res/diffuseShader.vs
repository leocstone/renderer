#version 120

attribute vec3 position;
attribute vec2 texCoord;
attribute vec3 normal;

varying vec2 texCoord0;
varying vec3 normal0;
varying vec3 fragPos;
varying vec3 viewPos0;

uniform mat4 transform;
uniform mat4 model;
uniform vec3 viewPos;

void main()
{
	gl_Position = transform * vec4(position, 1.0);
	texCoord0 = texCoord;
	normal0 = (model * vec4(normal, 0.0)).xyz;
    viewPos0 = viewPos;
    fragPos = vec3(model * vec4(position, 1.0));
}
