#version 330 core

in vec3 vertColor;

out vec4 FragColor;

void main(){
    FragColor = vec4(vertColor, 1.0);
    FragColor = vec4(1.0, 1.0, 0.0, 1.0);
}
