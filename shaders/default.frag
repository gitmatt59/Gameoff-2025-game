#version 330 core
out vec4 Color;
  
//in vec3 zoneColor;
//in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    Color=vec4(0.9f,0.5f,0.7f,1.0f);
}
