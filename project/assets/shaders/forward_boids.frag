#version 430 core

out vec4 FragColor;

in vec2 TexCoord;
in vec4 Normal;
in vec4 Position;


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
uniform sampler2D texture1;
uniform vec3 cameraEye;

float alpha_fog() {
    const float FogMax = 40.0;
    const float FogMin = 10.0;

    float d = distance(cameraEye, Position.xyz);
    if (d>=FogMax) return 1;
    if (d <=FogMin) return 0;
    return 1 - (FogMax -d) / (FogMax - FogMin);
}

void main()
{
    float alpha = alpha_fog();

    vec3 tex = texture(texture1, TexCoord).rgb;

    vec3 ambient = light.ambient * tex;
    vec3 norm = normalize(Normal.xyz);
    vec3 lightDir = normalize(-light.dir);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * tex;

    vec3 viewDir = normalize(cameraEye - Position.xyz);
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(norm, halfwayDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec;

    vec3 finalColor = ambient + diffuse + specular;

    FragColor = mix(vec4(finalColor, 1.0), vec4(light.ambient, 1.0), alpha);
}