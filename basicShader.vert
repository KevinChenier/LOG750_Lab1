#version 400 core
in vec4 vPosition;
in vec3 vNormal;
out vec3 fNormal;

void
main()
{
    gl_Position = vPosition;
    fNormal = vNormal;
}
