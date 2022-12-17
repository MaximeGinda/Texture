#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertices_position_modelspace;
layout(location = 1) in vec2 vertexUV;

uniform mat4 mvp;
uniform sampler2D heightMapSampler;

out vec2 UV;

void main(){

        vec4 position = vec4(vertices_position_modelspace,1);
        //position.z = texture(heightMapSampler,vertexUV).r;
        gl_Position = mvp * position;

        UV = vertexUV;
}

