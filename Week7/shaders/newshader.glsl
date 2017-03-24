#version  330  core

uniform  sampler2D  diffuse;
uniform  sampler2D  normals;
uniform  sampler2D  depth;
uniform sampler2D hatseflats;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 lightPos;

in vec3 FragPos;
in vec2 uv;

layout (location = 0) out  vec4  fColor;
layout (location = 1) out vec4 vertex;

void  main()
{
    float zValue;
    zValue = texture(depth, uv).z;

    zValue = (zValue * 2) - 1;

    vec3 FragPos2;
    FragPos2 = vec3(uv, zValue);

    vertex = vec4(FragPos2, 1.0) * inverse(projection * view * model);
    fColor = vec4(texture(hatseflats , uv).rgb , 1);
}
