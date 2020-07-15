#version 430 core
layout (location = 0) in vec4 aPos;
layout (location = 1) in vec4 pos;
layout (location = 2) in vec4 dir;

out vec4 color;
uniform mat4 projectionView;

#define eps 0.005

vec3 orthogonal(vec3 v) {
    float x = abs(v.x);
    float y = abs(v.y);
    float z = abs(v.z);

    vec3 other = x < y ? (x < z ? vec3(1, 0, 0) : vec3(0, 0, 1)) : (y < z ? vec3(0, 1, 0) : vec3(0, 0, 1));
    return cross(v, other);
}

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

void main()
{
    vec4 quat_rotation = get_rotation_between(vec3(1, 0, 0), dir.xyz);

    gl_Position = projectionView * vec4(rotate(quat_rotation, aPos.xyz) + pos.xyz, 1.0f);
    color = vec4(0.5, 0.1, 0.2, 1.0);
}