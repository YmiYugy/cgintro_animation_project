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

float map(float value, float min1, float max1, float min2, float max2) {
    return min2 + (value - min1) * (max2 - min2) / (max1 - min1);
}

vec4 hsva2rgba(vec4 hsva) {
    int h = int(map(hsva[0], 0, 1, 0, 360));
    float s = hsva[1];
    float v = hsva[2];
    float a = hsva[3];

    int h2 = int(floor(h/60.0));
    float f = (h/60.0-float(h2));
    float p = v * (1 - s);
    float q = v * (1 - s * f);
    float t = v * (1 - s * (1 - f));

    if (h2 == 1) return vec4(q, v, p, a);
    if (h2 == 2) return vec4(p, v, t, a);
    if (h2 == 3) return vec4(p, q, v, a);
    if (h2 == 4) return vec4(t, p, v, a);
    if (h2 == 5) return vec4(v, p, q, a);
    return vec4(v, t, p, a);
}


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