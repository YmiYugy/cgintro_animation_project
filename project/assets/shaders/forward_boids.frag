#version 430 core

out vec4 FragColor;

in vec2 TexCoord;
in vec4 Normal;
in vec4 Position;

uniform sampler2D texture1;
uniform vec3 CameraEye;
uniform vec4 LightColor;
uniform vec3 LightPos;

float alpha_fog() {
    const float FogMax = 40.0;
    const float FogMin = 10.0;

    float d = distance(CameraEye, Position.xyz);
    if (d>=FogMax) return 1;
    if (d <=FogMin) return 0;
    return 1 - (FogMax -d) / (FogMax - FogMin);
}

void main()
{

    float alpha = alpha_fog();

    const float ambientStrength = 0.3;
    vec4 ambient = ambientStrength * LightColor;

    vec3 norm = normalize(Normal.xyz);
    vec3 lightDir = normalize(LightPos - Position.xyz);
    float diff = max(dot(norm, lightDir), 0.0);
    vec4 diffuse = diff * LightColor;

    const float specularStrength = 1;
    vec3 viewDir = normalize(CameraEye - Position.xyz);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec4 specular = specularStrength * spec * LightColor;

    vec4 textureColor = texture(texture1, TexCoord);

    vec4 finalColor = (ambient + diffuse + specular) * textureColor;

    FragColor = mix(finalColor, vec4(2.0/255.0, 123.0/255.0, 150.0/255.0, 1.0), alpha);
}