#version 120

attribute vec2 position;
attribute vec2 texCoord;

varying vec2 texCoord0;

void main()
{
    gl_Position = vec4(position.x, position.y, 0.0, 1.0);
    texCoord0 = texCoord;
}
