#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertices_position_modelspace;
layout(location = 1) in vec2 vertexUV;

//TODO create uniform transformations matrices Model View Projection
// Values that stay constant for the whole mesh.

uniform mat4 mvp;

out vec2 UV;

uniform sampler2D normalMapSampler;

void main(){

        // TODO : Output position of the vertex, in clip space : MVP * position
        gl_Position = mvp * vec4(vertices_position_modelspace,1);

        gl_Position.z=-texture(normalMapSampler,vertexUV).r;

        UV = vertexUV;
}

