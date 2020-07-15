#version 430 core

out vec4 FragColor;

in vec2 TexCoord;
in vec4 Normal;
in vec4 Position;
in vec4 FragPosLightSpace;


struct Material {
    vec3 specular;
    float shininess;
};

struct Light {
    vec3 dir;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Light light;
uniform Material material;
uniform sampler2D diffuseTexture;
uniform sampler2D shadowMap;
uniform vec3 cameraEye;


float alpha_fog() {
    const float FogMax = 40.0;
    const float FogMin = 10.0;

    float d = distance(cameraEye, Position.xyz);
    if (d>=FogMax) return 1;
    if (d <=FogMin) return 0;
    return 1 - (FogMax -d) / (FogMax - FogMin);
}

float calculate_shadow(vec4 posLightSpace, float bias) {
    vec3 projCoords = posLightSpace.xyz / posLightSpace.w;
    projCoords = projCoords * 0.5 + 0.5;
    float closestDepth = texture(shadowMap, projCoords.xy).r;
    float currentDepth = projCoords.z;
    float shadow = currentDepth - bias > closestDepth  ? 1.0 : 0.0;

    return shadow;
}

void main()
{
    float alpha = alpha_fog();


    vec3 tex = texture(diffuseTexture, TexCoord).rgb;
    vec3 normal = normalize(Normal.xyz);

    vec3 lightDir = normalize(-light.dir);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff;

    vec3 viewDir = normalize(cameraEye - Position.xyz);
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, halfwayDir), 0.0), 64);
    vec3 specular = light.specular * spec;

    float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005);
    float shadow = calculate_shadow(FragPosLightSpace, bias);
    vec3 color = (light.ambient + (1.0 - shadow) * (diffuse + specular)) * tex;

    FragColor = mix(vec4(color, 1.0), vec4(light.ambient, 1.0), alpha);
}