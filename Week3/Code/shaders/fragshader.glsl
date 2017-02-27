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
in vec3 normal;
in vec3 FragPos;
in vec3 P;

uniform vec3 objCol;
uniform vec4 intensities;
uniform vec3 matColor;
uniform vec3 lightPos;

void main()
{
    vec3 lightColor = vec3(1,1,1);
    vec3 cameraPosition = vec3(0, 0, 0);
    vec3 finalColor, R;

    vec3 norm = normalize(normal);
    vec3 lightDir = (lightPos - FragPos);

    vec3 ambient = intensities[0] * lightColor;

    float diff = max(dot(norm, normalize(lightDir)), 0.0);
    vec3 diffuse = diff * lightColor;

    R = (2*(dot(norm,normalize(lightDir)))*norm) - normalize(lightDir);
    vec3 specular = pow(max(0.0,dot(normalize(-FragPos),R)),intensities[3]) * intensities[2] * lightColor;

    finalColor = (specular + ambient + diffuse) * matColor;
    fColor = vec4(finalColor, 1);
}
