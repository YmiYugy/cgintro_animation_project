#version 430

layout (location = 0) in vec4 aPos;
layout (location = 3) in vec4 pos;
layout (location = 4) in vec4 dir;

uniform mat4 model;
uniform mat4 projView;

vec4 get_rotation_between(vec3 u, vec3 v) {
    vec4 q;
    vec3 v0 = normalize(u);
    vec3 v1 = normalize(v);

    float d = dot(v0, v1);

    if (d < (eps - 1.0)) {
        q = vec4(normalize(orthogonal(u)), 0);
    } else {
        float s = sqrt((1+d)*2);
        float invs = 1/s;

        vec3 c = cross(v0, v1);

        q.x = c.x * invs;
        q.y = c.y * invs;
        q.z = c.z * invs;
        q.w = s * 0.5;
        q = normalize(q);
    }
    return q;
}

vec3 rotate(vec4 quaternion, vec3 vec) {
    return vec + 2.0 * cross(quaternion.xyz, cross(quaternion.xyz, vec) + quaternion.w * vec);
}

void main() {
    vec4 quat_rotation = get_rotation_between(vec3(1, 0, 0), dir.xyz);
    vec4 pos = vec4(rotate(quat_rotation, (model * aPos).xyz) + pos.xyz, 1.0f);
    gl_Position = projectionView * pos;
}