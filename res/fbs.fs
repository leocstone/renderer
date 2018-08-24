#version 120

varying vec2 texCoord0;

uniform sampler2D screenTexture;

const float offset = 1 / 4000.0;

float blurKernel[9] = float[](
        0.0625, 0.125, 0.0625,
        0.125, 0.25, 0.125,
        0.0625, 0.125, 0.0625
    );

float sharpenKernel[9] = float[](
        0, -1, 0,
        -1, 5, -1,
        0, -1, 0
    );

float sharpenKernel2[9] = float[](
        0.5, -2, -0.5,
        -2, 9, -2,
        0, -2, -0.5
    );

float leftSobel[9] = float[](
        1, 0, -1,
        2, 0, -2,
        1, 0, -1
    );

float rightSobel[9] = float[](
        -1, 0, 1,
        -2, 0, 2,
        -1, 0, 1
    );

float bottomSobel[9] = float[](
        -1, -2, -1,
        0, 0, 0,
        1, 2, 1
    );

float topSobel[9] = float[](
        1, 2, 1,
        0, 0, 0,
        -1, -2, -1
    );

// this is effectively the gamma, range from 2 to 2.7?
const float colorCorrectPower = 3;

vec3 CorrectColor(vec3 v)
{
    float brightness = pow(10.0f, colorCorrectPower / 4);
    return pow(v, vec3(colorCorrectPower)) * brightness;
}

void main()
{
    //gl_FragColor = texture2D(screenTexture, texCoord0);
    vec2 offsets[9] = vec2[](
        vec2(-offset,  offset), // top-left
        vec2( 0.0f,    offset), // top-center
        vec2( offset,  offset), // top-right
        vec2(-offset,  0.0f),   // center-left
        vec2( 0.0f,    0.0f),   // center-center
        vec2( offset,  0.0f),   // center-right
        vec2(-offset, -offset), // bottom-left
        vec2( 0.0f,   -offset), // bottom-center
        vec2( offset, -offset)  // bottom-right    
    );

    

    vec3 sampleTex[9];
    for(int i = 0; i < 9; i++)
    {
        sampleTex[i] = vec3(texture2D(screenTexture, texCoord0.st + offsets[i]));
    }
    vec3 col = vec3(0.0);
    for(int i = 0; i < 9; i++)
    {
        col += vec3(texture2D(screenTexture, texCoord0)) * 0.3;
        col += sampleTex[i] * sharpenKernel[i] * 0.1;
        //col += sampleTex[i] * blurKernel[i] * 5;
        //col += vec3(sampleTex[i].r * leftSobel[i] + sampleTex[i].r * bottomSobel[i], sampleTex[i].g * 0.1, sampleTex[i].b * rightSobel[i] + sampleTex[i].b * topSobel[i]);
    }

    // Blur pass
    /*
       for(int i = 0; i < 9; i++)
        {
            col += sampleTex[i] * blurKernel[i] * 2;
        }
    */    

    //gl_FragColor = vec4(col * col * col * col * col * 200, 1.0);
    //gl_FragColor = vec4(CorrectColor(col), 1.0);
    gl_FragColor = vec4(col - vec3(0.1), 1.0);
}

/*

    vec2 offsets[9] = vec2[](
        vec2(-offset,  offset), // top-left
        vec2( 0.0f,    offset), // top-center
        vec2( offset,  offset), // top-right
        vec2(-offset,  0.0f),   // center-left
        vec2( 0.0f,    0.0f),   // center-center
        vec2( offset,  0.0f),   // center-right
        vec2(-offset, -offset), // bottom-left
        vec2( 0.0f,   -offset), // bottom-center
        vec2( offset, -offset)  // bottom-right    
    );

    float kernel[9] = float[](
        -1, -1, -1,
        -1,  9, -1,
        -1, -1, -1
    );

    vec3 sampleTex[9];
    for(int i = 0; i < 9; i++)
    {
        sampleTex[i] = vec3(texture(screenTexture, texCoord0.st + offsets[i]));
    }
    vec3 col = vec3(0.0);
    for(int i = 0; i < 9; i++)
    {
        col += sampleTex[i] * kernel[i];
    }

    gl_FragColor = vec4(col, 1.0);

*/
