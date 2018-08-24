#version 120

varying vec2 texCoord0;
varying vec3 normal0;
varying vec3 viewPos0;
varying vec3 fragPos;

uniform sampler2D diffuse;

struct Material
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};
uniform Material material;

struct PointLight
{
    vec3 position;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float linear;
    float quadratic;
};

struct DirectionalLight
{
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct SpotLight
{
    vec3 position;
    vec3 direction;

    float cutOff;
    float outerCutOff;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    // Attenuation constants
    float linear;
    float quadratic;
};
uniform DirectionalLight directionalLight;

// Max point lights*
//#define NUM_POINT_LIGHTS 4
//uniform PointLight pointLights[NUM_POINT_LIGHTS];

// Orange street light color - 1.0f, 0.7216f, 0.3569f
// Moonlight color - 0.4431f, 0.3569f, 1.0f (Darker) OR 0.3569f, 0.8275f, 1.0f (Lighter)

// Dark moonlight - vec3(0.4431f, 0.3569f, 1.0f) for city
// Lighter moonlight - vec3(0.3569f, 0.8275f, 1.0f) for swamp

vec3 CalcDirLight(DirectionalLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);

    // Diffuse
    float diff = max(dot(normal, lightDir), 0.0);
    
    // Specular
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    vec3 ambient = light.ambient * vec3(texture2D(diffuse, texCoord0));
    vec3 diffuseColor = light.diffuse * diff * vec3(texture2D(diffuse, texCoord0)) * material.diffuse;
    vec3 specular = light.specular * spec * vec3(texture2D(diffuse, texCoord0)) * material.specular;
    return (ambient + diffuseColor + specular);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);

    // Diffuse
    float diff = max(dot(normal, lightDir), 0.0);

    // Specular
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    // Attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (1.0 + light.linear * distance + light.quadratic * (distance * distance));

    vec3 ambient = light.ambient * vec3(texture2D(diffuse, texCoord0));
    vec3 diffuseColor = light.diffuse * diff * vec3(texture2D(diffuse, texCoord0)) * material.diffuse;
    vec3 specular = light.specular * spec * vec3(texture2D(diffuse, texCoord0)) * material.specular;

    ambient *= attenuation;
    diffuseColor *= attenuation;
    specular *= attenuation;
    return (ambient + diffuseColor + specular);
}

// TODO This
vec3 CalcInversePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);

    // Diffuse
    float diff = max(dot(normal, lightDir), 0.0);

    // Specular
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    // Attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (1.0 + light.linear * distance + light.quadratic * (distance * distance));

    vec3 ambient = light.ambient * vec3(texture2D(diffuse, texCoord0));
    vec3 diffuseColor = light.diffuse * diff * vec3(texture2D(diffuse, texCoord0)) * material.diffuse;
    vec3 specular = light.specular * spec * vec3(texture2D(diffuse, texCoord0)) * material.specular;

    ambient *= attenuation;
    diffuseColor *= attenuation;
    specular *= attenuation;
    return (ambient + diffuseColor + specular);
}

vec3 skyColor = vec3(0.1, 0.2, 1.0);

void main()
{
    if(texture2D(diffuse, texCoord0).a < 0.1)
    {
	discard;
    }
    vec3 norm = normalize(normal0);
    vec3 viewDir = normalize(viewPos0 - fragPos);

    vec3 result = CalcDirLight(directionalLight, norm, viewDir);
    PointLight playerLight;
    playerLight.position = viewPos0;
    playerLight.ambient = vec3(1.0f, 0.7216f, 0.3569f) * 0.1;
    playerLight.diffuse = vec3(1.0f, 0.7216f, 0.3569f) * 0.5;
    playerLight.specular = vec3(1.0, 1.0, 1.0) * 0.0;
    playerLight.linear = 0.001;
    playerLight.quadratic = 0.001;

    //result += CalcPointLight(playerLight, norm, fragPos, viewDir);

    /*for(int i = 0; i < NUM_POINT_LIGHTS; i++)
    {
        result += CalcPointLight(pointLights[i], norm, fragPos, viewDir);
    }*/
    float fade = length(viewPos0 - fragPos) / 1000.0f;
    fade *= fade;
    gl_FragColor = vec4(result + fade * skyColor, 1.0);
}

