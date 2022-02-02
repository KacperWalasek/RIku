#version 330 core
out vec4 FragColor;

uniform vec4 color;

uniform vec4 fog_color;
uniform float fog_density;

in vec4 ioEyeSpacePosition;

vec4 FogColor(vec4 my_color, float fog_c)
{
   vec4 ret;
   float ci_o=1.0f/exp(fog_c*fog_c*fog_density*fog_density);
   float ci_f=1.0f-ci_o;
   ret.r=ci_o * my_color.r + ci_f * fog_color.r;
   ret.g=ci_o * my_color.g + ci_f * fog_color.g;
   ret.b=ci_o * my_color.b + ci_f * fog_color.b;
   ret.a=1.0f;
   return ret;
}

void main()
{
   float fogCoordinate = abs(ioEyeSpacePosition.z / ioEyeSpacePosition.w);
   FragColor=FogColor(color, fogCoordinate);
}