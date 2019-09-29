#version 400 core
uniform vec3 uAmbientLighting;
uniform vec3 uDiffuseLighting;
uniform vec3 uSpecularLighting;
uniform vec3 uLightingPosition;
uniform float uSpecularExponent;
uniform bool uSecondLight;
in vec3 fPosition;
in vec3 fNormal;
out vec4 fColor;

void
main()
{
    // Get lighting vectors
    vec3 LightDirection = normalize(uLightingPosition - fPosition); // Point light centered at (1, 1, 1)
    vec3 nfNormal = normalize(fNormal);

    // Compute diffuse component
    float diffuse = max(0.0,dot(nfNormal, LightDirection));

    // Compute specular component
    vec3 reflection = normalize(reflect(-LightDirection, nfNormal));
    vec3 nviewDirection = normalize(-fPosition + vec3(0.0, 0.0, -1.0));
    float specular = pow(max(0.0, dot(reflection, nviewDirection)), uSpecularExponent);

    if(uSecondLight){
        vec3 secondLightDirection = normalize(vec3(-1.0, 1.0, 1.0) - fPosition);
        float secondDiffuse = max(0.0,dot(nfNormal, secondLightDirection));
        vec3 secondReflection = normalize(reflect(-secondLightDirection, nfNormal));
        float secondSpecular = pow(max(0.0, dot(secondReflection, nviewDirection)), 1.0);

        fColor = vec4(uAmbientLighting + (uDiffuseLighting * diffuse + vec3(0.0, 0.0, 0.0) * secondDiffuse + uSpecularLighting * specular + vec3(0.4, 0.4, 0.4) * secondSpecular), 1);
    } else{
        // Compute final color
        fColor = vec4(uAmbientLighting + (uDiffuseLighting * diffuse + uSpecularLighting * specular), 1);
    }


}
