#version 400 core
in vec4 vPosition;
void
main()
{
     gl_Position = vPosition;
     // Pour le laboratoire 1 seulement :
     // Changement d'un système main gauche vers un système main droite en inversant le Z. Ainsi, nous
     // regardons du côté négatif de l'axe des Z.
     gl_Position = vec4(vPosition.xy, -vPosition.z, 1);
}

