#version 330 core

// Ouput/Input data
out vec3 color;

in vec2 UV;
in vec3 fragPos;

uniform sampler2D textureSampler;
uniform sampler2D normalMapSampler;

uniform vec3 lightPosition;
uniform vec3 lightColor;

uniform vec3 viewPos;

float shininess = 0.;
vec3 ambient = vec3(0,0,0);

void main(){

        // vec3 objColor = vec3(0,0,0);
        vec3 objColor = texture(textureSampler,UV).rgb;

        vec3 normal = 2 * texture(normalMapSampler, UV).xyz  - 1.0;

        vec3 lightDirection = normalize(lightPosition - fragPos);
        float diff = max(dot(normal, lightDirection), 0.0);
        vec3 diffuse = diff * lightColor;

        vec3 viewDirection = normalize(viewPos - fragPos);
        vec3 reflectDirection = reflect(-lightDirection, normal);
        float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), shininess);
        vec3 specular = spec * lightColor;

        color = (ambient + diffuse + specular);
}
