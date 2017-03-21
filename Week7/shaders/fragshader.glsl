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
in vec3 FragPos;
in vec3 normal;
in vec3 lightPosOut;

uniform vec3 objCol;
uniform vec4 intensities;
uniform vec3 matColor;
/*
void main()
{
    const vec3 lightColor = vec3(1,1,1);

    vec3 norm = normalize(normal);

    vec3 lightDir = normalize(lightPosOut - FragPos);
    vec3 R = -reflect(lightDir, norm);

    float comAmbient = intensities[0];
    float comDiffuse = max(dot(norm, lightDir), 0.0) * intensities[1];
    float comSpecular = pow(max(dot(R, vec3(0, 0, 1)), 0), intensities[3]) * intensities[2];

    vec3 finalColor =
            comAmbient * matColor +
            comDiffuse * matColor * lightColor +
            comSpecular * lightColor;

    fColor = vec4(finalColor, 1);
}
*/

void main()
{
    // Plain White
    //fColor = vec4(color, 1.0);

    //texture instead of texture2D, otherwise it will not work on system



    const vec3 lightColor = vec3(1,1,1);

    vec3 norm = normalize(normal);

    vec3 lightDir = normalize(lightPosOut - FragPos);
    vec3 R = -reflect(lightDir, norm);

    float comAmbient = 0.2;
    float comDiffuse = max(dot(norm, lightDir), 0.0) * 0.7;
    float comSpecular = pow(max(dot(R, vec3(0, 0, 1)), 0), 256) * 0.9;

    vec3 finalColor =
            comAmbient * texture(texUniform, vertexTexCoords).rgb +
            comDiffuse * texture(texUniform, vertexTexCoords).rgb * lightColor +
            comSpecular * lightColor;


    fColor = vec4(finalColor,1.0);

}
