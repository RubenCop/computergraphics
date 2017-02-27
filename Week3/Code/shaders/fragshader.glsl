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
in vec3 vertexCoordinates;
in vec3 norm;
in vec4 FragPos;
in vec3 P;

uniform vec3 objCol;
uniform vec4 intensities;
uniform vec3 matColor;
uniform vec3 lightPos;

void main()
{
    vec3 R;
    vec3 a = vec3(intensities[0],intensities[0],intensities[0]);
    vec3 i = vec3(1,1,1);
    vec3 light_pos = vec3(-200,600,1500);

    vec3 N = normalize(norm);
    vec3 L = normalize(lightPos - P);
    vec3 V = normalize(-P);
    R = 2 * dot(L,N) * N - L;
    vec3 col = 0.2*a + 1.0 * max(dot(L, N),0.) * i + 0.6 * pow( max(dot(R,V),0.) , 6.) * i;
    fColor = vec4(matColor * col, 1.0);
}
