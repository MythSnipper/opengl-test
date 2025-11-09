#version 330 core

in vec4 vertColor;
in vec2 vertTexCoord;

uniform sampler2D texture0;
uniform sampler2D texture1;

out vec4 FragColor;

void main(){
    FragColor = mix(texture(texture0, vertTexCoord), texture(texture1, vertTexCoord), 0.3);
}
