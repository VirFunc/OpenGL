#version 330 core
uniform vec3 lightColor;
out vec4 fragColor;
void main()
{
   fragColor=lightColor;
}