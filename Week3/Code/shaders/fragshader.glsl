#version 330 core

// Define constants
#define M_PI 3.141593

// Specify the inputs to the fragment shader
// These must have the same type and name!

// in vec3 vertPos; Using the output from the vertex shader example

// Specify the Uniforms of the vertex shaders
// uniform vec3 lightPosition; for example

// Specify the output of the fragment shader
// Usually a vec4 describing a color (Red, Green, Blue, Alpha/Transparency)
out vec4 fColor;
flat in vec3 color;

uniform vec3 objCol;
uniform vec4 intensities;
uniform vec3 lightPos;

void main()
{
    // Plain White
    fColor = vec4(color, 1.0); //of MaterialColor????
}
