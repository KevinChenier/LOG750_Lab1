#version 400 core
uniform vec3 uAmbientLighting;
uniform vec3 uDiffuseLighting;
uniform vec3 uSpecularLighting;
uniform float uSpecularExponent;
in vec3 fPosition;
in vec3 fNormal;
out vec4 fColor;

void
main()
{
    // Get lighting vectors
    vec3 LightDirection = normalize(vec3(1.0)); // Point light centered at (1, 1, 1)
    vec3 nfNormal = normalize(fNormal);
    vec3 nviewDirection = normalize(vec3(1.0) - fPosition);

    // Compute diffuse component
    float diffuse = dot(nfNormal, LightDirection);

    if (diffuse > 0.0)
    {
        // Compute specular component
        vec3 reflection = reflect(-LightDirection, nfNormal);
        vec3 nviewDirection = normalize(vec3(0.0));
        float specular = pow(max(0.0, dot(reflection, nviewDirection)), uSpecularExponent);

        // Compute final color
        fColor = vec4(uAmbientLighting + (uDiffuseLighting * diffuse +  uSpecularLighting * specular), 1);
        //fColor = vec4(uAmbientLighting, 1.0) + vec4(uDiffuseLighting, 1.0) * diffuse + vec4(uSpecularLighting, 1.0) * specular;
    }
    else
    {
        fColor = vec4(vec3(0.0), 1.0);
    }
}
