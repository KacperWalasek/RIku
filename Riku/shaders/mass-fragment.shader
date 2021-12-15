

#version 330 core
//layout (location = 3) in vec4 color_mod;

out vec4 FragColor;

struct Material {
   float shininess;
};

struct DirLight {
   vec3 direction;

   vec3 ambient;
   vec3 diffuse;
   vec3 specular;
};

struct PointLight {
   vec3 position;

   float constant;
   float linear;
   float quadratic;

   vec3 ambient;
   vec3 diffuse;
   vec3 specular;
};

struct SpotLight {
   vec3 position;
   vec3 direction;
   float cutOff;
   float outerCutOff;

   float constant;
   float linear;
   float quadratic;

   vec3 ambient;
   vec3 diffuse;
   vec3 specular;
};

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;
in vec4 ioEyeSpacePosition;

uniform vec3 viewPos;
uniform DirLight dirLight;
#define NR_POINT_LIGHTS 9
uniform PointLight pointLights[NR_POINT_LIGHTS];
#define NR_SPOT_LIGHTS 1
uniform SpotLight spotLights[NR_SPOT_LIGHTS];
uniform Material material;

vec4 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec4 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec4 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;

uniform vec4 fog_color;
uniform float fog_density;

vec4 FogColor(vec4 my_color, float fog_c)
{
   vec4 ret;
   float ci_o=1.0f/exp(fog_c*fog_c*fog_density*fog_density);
   float ci_f=1.0f-ci_o;
   ret.r=ci_o * my_color.r + ci_f * fog_color.r;
   ret.g=ci_o * my_color.g + ci_f * fog_color.g;
   ret.b=ci_o * my_color.b + ci_f * fog_color.b;
   ret.a=my_color.a;
   return ret;
}

void main()
{
   vec3 norm = normalize(Normal);
   vec3 viewDir = normalize(viewPos - FragPos);

   // phase 1: Directional lighting
   vec4 result = CalcDirLight(dirLight, norm, viewDir);
   // phase 2: Point lights
   for(int i = 0; i < NR_POINT_LIGHTS; i++)
      result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);
   // phase 3: Spot light
   for(int i = 0; i < NR_SPOT_LIGHTS; i++)
      result += CalcSpotLight(spotLights[i], norm, FragPos, viewDir);

   if(result.a < 0.1)
      discard;
   FragColor = result * color_mod;

   float fogCoordinate = abs(ioEyeSpacePosition.z / ioEyeSpacePosition.w);
   FragColor=FogColor(FragColor, fogCoordinate);
   //FragColor = texture(texture_diffuse1, TexCoords);
}

vec4 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
   vec3 lightDir = normalize(-light.direction);
   // diffuse shading
   float diff = max(dot(normal, lightDir), 0.0);
   // specular shading
   vec3 reflectDir = reflect(-lightDir, normal);
   float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
   // combine results
   vec3 ambient  = light.ambient  * texture(texture_diffuse1, TexCoords).rgb;
   vec3 diffuse  = light.diffuse  * diff * texture(texture_diffuse1, TexCoords).rgb;
   vec3 specular = light.specular * spec * texture(texture_specular1, TexCoords).rgb;
   return vec4(ambient + diffuse + specular, texture(texture_diffuse1, TexCoords).a);
}

vec4 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
   vec3 lightDir = normalize(light.position - fragPos);
   // diffuse shading
   float diff = max(dot(normal, lightDir), 0.0);
   // specular shading
   vec3 reflectDir = reflect(-lightDir, normal);
   float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
   // attenuation
   float distance    = length(light.position - fragPos);
   float attenuation = 1.0 / (light.constant + light.linear * distance +
   light.quadratic * (distance * distance));
   // combine results
   vec3 ambient  = light.ambient  * vec3(texture(texture_diffuse1, TexCoords));
   vec3 diffuse  = light.diffuse  * diff * vec3(texture(texture_diffuse1, TexCoords));
   vec3 specular = light.specular * spec * vec3(texture(texture_specular1, TexCoords));
   ambient  *= attenuation;
   diffuse  *= attenuation;
   specular *= attenuation;
   return vec4(ambient + diffuse + specular, texture(texture_diffuse1, TexCoords).a);
}

vec4 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
   vec3 lightDir = normalize(light.position - fragPos);
   // diffuse shading
   float diff = max(dot(normal, lightDir), 0.0);
   // specular shading
   vec3 reflectDir = reflect(-lightDir, normal);
   float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
   // attenuation
   float distance = length(light.position - fragPos);
   float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
   // spotlight intensity
   float theta = dot(lightDir, normalize(-light.direction));
   float epsilon = light.cutOff - light.outerCutOff;
   float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
   // combine results
   vec3 ambient = light.ambient * vec3(texture(texture_diffuse1, TexCoords));
   vec3 diffuse = light.diffuse * diff * vec3(texture(texture_diffuse1, TexCoords));
   vec3 specular = light.specular * spec * vec3(texture(texture_specular1, TexCoords));
   ambient *= attenuation * intensity;
   diffuse *= attenuation * intensity;
   specular *= attenuation * intensity;
   return vec4(ambient + diffuse + specular, texture(texture_diffuse1, TexCoords).a);
}
