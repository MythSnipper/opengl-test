#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 aTransform;

out vec4 vertColor;
out vec2 vertTexCoord;

void main(){
    gl_Position = aTransform * vec4(aPos, 1.0);
 
    vertColor = vec4(aColor, 1.0);
    vertTexCoord = aTexCoord;
}
