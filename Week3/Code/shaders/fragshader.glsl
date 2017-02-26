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

uniform vec3 objCol;
uniform vec4 intensities;
//uniform vec3 lightPos;

void main()
{
    vec3 tempCol = vec3(1,0,0);
    vec3 lightPos = vec3(-200,600,1500);
    vec3 lightColor = vec3(1,1,1);
    vec3 cameraPosition = vec3(0, 0, 0);
    vec3 finalColor, R;
    //fColor = vec4(color, 1.0); //of MaterialColor????
    //add ambient intensity
    /*
    finalColor = color*intensities[0];
    finalColor += (max(1.0, dot(lightPos, -normal)) * intensities[1]) * color * lightColor;
    R = (2*(dot(normal,lightPos))*normal)-lightPos;
    finalColor += pow(max(1.0, dot(R, vertexCoordinates)),intensities[3])*intensities[2];
    */

    vec3 ambient = intensities[0] * lightColor;

    vec3 norm = normalize(normal);
    vec3 lightDir = (lightPos - FragPos);

    float diff = max(dot(norm, normalize(lightDir)), 0.0);
    vec3 diffuse = diff * lightColor;

    //fColor = vec4(color, 1); //Works! But not with phong shading

    finalColor = (ambient + diffuse) * tempCol;
    fColor = vec4(finalColor, 1);
}
