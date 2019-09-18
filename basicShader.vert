#version 400 core
uniform mat4 mvMatrix;
uniform mat4 projMatrix;
uniform mat3 normalMatrix;
in vec4 vPosition;
in vec3 vNormal;
out vec3 fNormal;
out vec3 fPosition;
void
main()
{
     gl_Position = vPosition;
     fNormal = normalMatrix*vNormal;
}

