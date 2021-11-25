#version 460 core

in vec3 FragPos;

out vec4 FragColor;

uniform vec3 OurColor;

void main() {
    FragColor = vec4(OurColor, 1.0);
}