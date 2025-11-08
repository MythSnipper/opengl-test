#version 330 core

in vec3 vertColor;
in vec2 vertTexCoord;

uniform sampler2D texture0;
uniform sampler2D texture1;

out vec4 FragColor;

void main(){
    FragColor = texture(texture0, vertTexCoord) + vec4(0.0, 0.0, 0.0, 0.0);
}
