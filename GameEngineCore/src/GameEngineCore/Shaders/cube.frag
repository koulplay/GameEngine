#version 460
in vec3 frag_pos;
in vec3 normal;
in vec2 texture_cords;

out vec4 frag_color;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};
uniform Material material;

struct DirLight {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform DirLight dir_light;

struct PointLight {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};
#define NR_POINT_LIGHTS 4
uniform PointLight point_lights[NR_POINT_LIGHTS];

struct SpecLight {
    vec3 position;
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float cut_off;
    float outer_cut_off;
};
uniform SpecLight spec_light;

uniform vec3 view_pos;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 view_dir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 frag_pos, vec3 view_dir);
vec3 CalcSpotLight(SpecLight light, vec3 normal, vec3 frag_pos, vec3 view_dir);

void main() {
    vec3 norm = normalize(normal);
    vec3 view_dir = normalize(view_pos - frag_pos);

    vec3 result = CalcDirLight(dir_light, norm, view_dir);

    for(int i = 0; i < NR_POINT_LIGHTS; ++i) {
        result += CalcPointLight(point_lights[i], norm, frag_pos, view_dir);
    }

    //result += CalcSpotLight(spec_light, normal, frag_pos, view_dir);

    frag_color = vec4(result, 1.0);
}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 view_dir) {
    vec3 light_dir = normalize(-light.direction);
    float diff = max(dot(normal, light_dir), 0.0);

    vec3 reflect_dir = reflect(-light_dir, normal);
    float spec = pow(max(dot(view_dir, reflect_dir), 0.0), material.shininess);

    vec3 ambient  = light.ambient  * vec3(texture(material.diffuse, texture_cords));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse, texture_cords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, texture_cords));

    return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 frag_pos, vec3 view_dir) {
    vec3 light_dir = normalize(light.position - frag_pos);
    float diff = max(dot(normal, light_dir), 0.0);

    vec3 reflect_dir = reflect(-light_dir, normal);
    float spec = pow(max(dot(view_dir, reflect_dir), 0.0), material.shininess);

    float distance    = length(light.position - frag_pos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    vec3 ambient  = light.ambient * vec3(texture(material.diffuse, texture_cords));
    vec3 diffuse  = light.diffuse * diff * vec3(texture(material.diffuse, texture_cords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, texture_cords));

    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;

    return (ambient + diffuse + specular);
}

vec3 CalcSpotLight(SpecLight light, vec3 normal, vec3 frag_pos, vec3 view_dir) {
    vec3 light_dir  = normalize(light.position - frag_pos);

    float theta     = dot(light_dir, normalize(-light.direction));
    float epsilon   = light.cut_off - light.outer_cut_off;
    float intensity = clamp((theta - light.outer_cut_off) / epsilon, 0.0, 1.0);

    if (theta > light.outer_cut_off) {
        float diff = max(dot(normal, light_dir), 0.0);

        vec3 reflect_dir = reflect(-light_dir, normal);
        float spec = pow(max(dot(view_dir, reflect_dir), 0.0), material.shininess);

        vec3 ambient  = light.ambient * vec3(texture(material.diffuse, texture_cords));
        vec3 diffuse  = light.diffuse * diff * vec3(texture(material.diffuse, texture_cords));
        vec3 specular = light.specular * spec * vec3(texture(material.specular, texture_cords));

        ambient  *= intensity;
        diffuse  *= intensity;
        specular *= intensity;

        return (ambient + diffuse + specular);
    }
    else {
        return light.ambient * vec3(texture(material.diffuse, texture_cords));
    }
}