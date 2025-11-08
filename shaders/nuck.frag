#version 330 core

in vec3 vertColor;
in vec2 vertTexCoord;

uniform sampler2D aTexture;

out vec4 FragColor;

void main(){
    FragColor = (0.5 * texture(aTexture, vertTexCoord)) + (1.3 * vec4(vertColor, 1.0));
}
