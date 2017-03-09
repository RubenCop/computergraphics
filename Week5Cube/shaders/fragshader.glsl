#version 330 core

// Define constants
#define M_PI 3.141593

// Specify the inputs to the fragment shader
// These must have the same type and name!

// in vec3 vertPos; Using the output from the vertex shader example

// Specify the Uniforms of the vertex shaders
// uniform vec3 lightPosition; for example

uniform sampler2D texUniform;

// Specify the output of the fragment shader
// Usually a vec4 describing a color (Red, Green, Blue, Alpha/Transparency)
out vec4 fColor;
flat in vec3 color;
in vec2 vertexTexCoords;

void main()
{
    // Plain White
    //fColor = vec4(color, 1.0);
    fColor = texture2D(texUniform, vertexTexCoords);

}
