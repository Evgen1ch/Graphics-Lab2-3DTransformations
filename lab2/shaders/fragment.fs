// #version 460 core

// in vec3 FragPos;
// in vec3 Normal;
// in vec2 TexCoords;

// out vec4 FragColor;

// struct Material {
//     sampler2D texture_diffuse1;
//     sampler2D texture_specular1;

//     float shininess;
// };

// struct PointLight {
//     vec3 ambient;
//     vec3 diffuse;
//     vec3 specular;

//     vec3 position;
// };

// //function prototypes
// vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

// //uniforms
// uniform Material material;
// uniform PointLight pointLight;
// uniform vec3 viewPos;

// void main() {
//     vec3 norm = normalize(Normal);
//     vec3 viewDir = normalize(viewPos - FragPos);

//     vec3 result = CalculatePointLight(pointLight, norm, FragPos, viewDir);

//     FragColor = vec4(result, 1.0);
// }

// vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
//     vec3 lightDir = normalize(light.position - fragPos);
//     vec3 ambient = light.ambient * vec3(texture(material.texture_diffuse1, TexCoords));
//     //diffuse
//     float diff = max(dot(normal, lightDir), 0.0);
//     vec3 diffuse = light.diffuse * diff * vec3(texture(material.texture_diffuse1, TexCoords));
//     //specular
//     vec3 reflectDir = reflect(-lightDir, normal);
//     float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
//     vec3 specular = light.specular * spec * vec3(texture(material.texture_specular1, TexCoords));

//     return (ambient + diffuse + specular);
// }

#version 460 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

struct DirLight {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct Material {
    sampler2D texture_diffuse1;
    sampler2D texture_specular1;

    float shininess;
};

uniform Material material;
uniform DirLight dirLight;
uniform vec3 viewPos;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir) {
    vec3 lightDir = normalize(-light.direction);

    float diff = max(dot(normal, lightDir), 0.0);

    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    vec3 diffuseMaterial = vec3(texture(material.texture_diffuse1, TexCoords));
    vec3 specularMaterial = vec3(texture(material.texture_specular1, TexCoords));

    vec3 ambient = light.ambient * diffuseMaterial;
    vec3 diffuse = light.diffuse * diff * diffuseMaterial;
    vec3 specular = light.specular * spec * specularMaterial;
    return ambient + diffuse + specular;
}

void main()
{   
    vec3 normal = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    vec3 result = CalcDirLight(dirLight, normal, viewDir);

    FragColor = vec4(result, 1.0);
}