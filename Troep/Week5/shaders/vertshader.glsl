#version 330 core

// Define constants
#define M_PI 3.141593

// Specify the input locations of attributes
layout (location = 0) in vec3 vertCoordinates_in;
layout (location = 1) in vec3 vertColor_in;
layout (location = 2) in vec3 vertNormal_in;
layout (location = 3) in vec2 vertTexture_in;

// Specify the Uniforms of the vertex shader
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
//uniform vec4 intensities;

uniform mat3 normalMatrix;
uniform vec3 lightPos;

// uniform mat4 modelTransform; for example

// Specify the outputs of the vertex shader
// These will be the input for the fragment shader

// out vec3 vertPos; for example
out vec3 normal;
out vec3 FragPos;
out vec3 lightPosOut;
out vec2 vertexTexCoords;

void main()
{
    // gl_Position is the output (a vec4) of the vertex shader
    // Currently without any transformation
    lightPosOut = mat3(view) * mat3(model) * lightPos;
    FragPos = vertCoordinates_in;

    gl_Position = projection * view * model * vec4(vertCoordinates_in, 1.0);
    normal = normalMatrix * vertColor_in;

    vertexTexCoords = vertTexture_in;


}
