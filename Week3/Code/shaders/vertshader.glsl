#version 330 core

// Define constants
#define M_PI 3.141593

// Specify the input locations of attributes
layout (location = 0) in vec3 vertCoordinates_in;
layout (location = 1) in vec3 vertColor_in;
layout (location = 2) in vec3 vertNormal_in;

// Specify the Uniforms of the vertex shader
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
//uniform vec4 intensities;

uniform mat4 normalMatrix;

// uniform mat4 modelTransform; for example

// Specify the outputs of the vertex shader
// These will be the input for the fragment shader

// out vec3 vertPos; for example
flat out vec3 color;
out vec3 vertexCoordinates;
out vec3 norm;
out vec3 P;
//out vec4 intensities;

void main()
{
    vec3 normalMat;
    // gl_Position is the output (a vec4) of the vertex shader
    // Currently without any transformation

    vec4 mv_pos = (view * model) * vec4(vertCoordinates_in, 1);

    gl_Position = projection * mv_pos;

    normalMat = mat3(transpose(inverse(model))) * vertColor_in;

    norm = vertCoordinates_in;


    P = mv_pos.xyz / mv_pos.w;

}
