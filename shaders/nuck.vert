#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 aModel;
uniform mat4 aView;
uniform mat4 aProjection;

out vec4 vertColor;
out vec2 vertTexCoord;

void main(){
    gl_Position = aProjection * aView * aModel * vec4(aPos, 1.0);
 
    vertColor = vec4(aColor, 1.0);
    vertTexCoord = aTexCoord;
}
