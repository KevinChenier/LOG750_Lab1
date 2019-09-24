#version 400 core
uniform vec3 uAmbientLighting;
uniform vec3 uDiffuseLighting;
uniform vec3 uSpecularLighting;
uniform vec3 uLightingPosition;
uniform float uSpecularExponent;
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
    float diffuse = dot(nfNormal, LightDirection);

    // Compute specular component
    vec3 reflection = reflect(-LightDirection, nfNormal);
    vec3 nviewDirection = vec3(0.0, 0.0, -1.0);   // fPosition - vec3(0.0,0.0,1.0);
    float specular = pow(max(0.0, dot(reflection, nviewDirection)), uSpecularExponent);

    // Compute final color
    fColor = vec4(uAmbientLighting + (uDiffuseLighting * diffuse +  uSpecularLighting * specular), 1);
}
