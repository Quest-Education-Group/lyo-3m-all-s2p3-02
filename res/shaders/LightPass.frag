#version 450 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gAlbedoSpec;
uniform sampler2D shadowMap;
uniform sampler2D gSkybox;

struct Light {
    vec3 Color;
    vec4 Direction;
    
    float Linear;
    float Quadratic;
    float Radius;
};

const int NR_LIGHTS = 32;
uniform Light lights[NR_LIGHTS];
uniform vec3 viewPos;
uniform int nbLights;

uniform mat4 lightSpaceMatrix;

float ShadowCalculation(vec4 fragPosLightSpace)
{
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    projCoords = projCoords * 0.5 + 0.5;

    float closestDepth = texture(shadowMap, projCoords.xy).r;
    float currentDepth = projCoords.z;

    float shadow = currentDepth > closestDepth ? 1.0 : 0.0;

    return shadow;
}

void main()
{             
    // retrieve data from gbuffer
    vec3 FragPos = texture(gPosition, TexCoords).rgb;
    vec3 Normal = texture(gNormal, TexCoords).rgb;
    vec3 Diffuse = texture(gAlbedoSpec, TexCoords).rgb;
    float Specular = texture(gAlbedoSpec, TexCoords).a;
    vec4 FragPosLightSpace = lightSpaceMatrix * vec4(FragPos, 1.0);
    
    // then calculate lighting as usual
    vec3 lighting  = Diffuse * vec3(0.1f); // hard-coded ambient component
    vec3 viewDir  = normalize(viewPos - FragPos);
    for(int i = 0; i < nbLights; ++i)
    {
        if(lights[i].Direction.w <= 0.001)
        {
            vec3 lightDir = normalize(-lights[i].Direction.xyz);
            vec3 diff = max(dot(Normal, lightDir), 0.0) * Diffuse * lights[i].Color;
            vec3 halfwayDir = normalize(lightDir + viewDir);  
            float spec = pow(max(dot(Normal, halfwayDir),0.0), 16.0);
            vec3 specular = lights[i].Color * spec * Specular;
            float shadow = ShadowCalculation(FragPosLightSpace);

            lighting += (1.0 - shadow) * (diff + specular)
            continue;
        }

        // calculate distance between light source and current fragment
        vec3 Position = lights[i].Direction.xyz;
        float distance = length(Position - FragPos);
        if(distance < lights[i].Radius)
        {
            // diffuse
            vec3 lightDir = normalize(Position - FragPos);
            vec3 diffuse = max(dot(Normal, lightDir), 0.) * Diffuse * lights[i].Color;
            // specular
            vec3 halfwayDir = normalize(lightDir + viewDir);  
            float spec = pow(max(dot(Normal, halfwayDir), 0.0), 16.0);
            vec3 specular = lights[i].Color * spec * Specular;
            // attenuation
            float attenuation = 1.0 / (1.0 + lights[i].Linear * distance + lights[i].Quadratic * distance * distance);
            diffuse *= attenuation;
            specular *= attenuation;
            lighting += diffuse + specular;
        }
    }

    FragColor = texture(gSkybox, TexCoords) * (1 - Specular) + vec4(lighting, Specular);
    //FragColor = vec4(lighting, 1.0);
}
