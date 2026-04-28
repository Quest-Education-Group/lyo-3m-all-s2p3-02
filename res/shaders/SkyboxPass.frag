#version 450 core
layout (location = 0) out vec3 gPosition;
layout (location = 1) out vec3 gNormal;
layout (location = 2) out vec4 gAlbedoSpec;
layout (location = 3) out vec4 gSkybox;

in vec3 TexCoords;
out vec4 FragColor;

uniform samplerCube skybox;

void main()
{
    //gAlbedoSpec.rgb = texture(skybox, TexCoords).rgb;
    //gAlbedoSpec.a = 1.0f;
    gSkybox = texture(skybox, -TexCoords);
}