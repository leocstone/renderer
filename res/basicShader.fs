#version 120

varying vec2 texCoord0;
varying vec3 normal0;

uniform sampler2D diffuse;

// Orange street light color - 1.0f, 0.7216f, 0.3569f
// Moonlight color - 0.4431f, 0.3569f, 1.0f (Darker) OR 0.3569f, 0.8275f, 1.0f (Lighter)

// Dark moonlight - vec3(0.4431f, 0.3569f, 1.0f)
// Lighter moonlight - vec3(0.3569f, 0.8275f, 1.0f)

vec3 shift_to_black(vec3 v)
{
    float minValue = min(v.r, min(v.g, v.b));

    v -= minValue * 1.3;
    v.r *= 20;
    v.b *= 4;
    return v;
}

void main()
{
	// Half-lambert shading is turned off (* clamp(dot(-vec3(0, 0, 1), normal0), 0.0, 1.0))
	gl_FragColor = texture2D(diffuse, texCoord0);
}

