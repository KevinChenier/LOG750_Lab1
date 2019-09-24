#version 400 core
in vec4 vPosition;
in vec3 vNormal;
out vec3 fNormal;
out vec3 fPosition;

void
main()
{
    gl_Position = vPosition;
    fPosition = vPosition.xyz;
    fNormal = vNormal;
}
