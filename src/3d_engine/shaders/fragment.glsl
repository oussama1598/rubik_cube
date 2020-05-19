#version 440

struct Material
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 vs_position;
in vec3 vs_color;
in vec2 vs_text_coordinates;
in vec3 vs_normal;

out vec4 fs_color;

uniform Material material;

void main() {
    fs_color = vec4(material.diffuse, 1.f);
}
