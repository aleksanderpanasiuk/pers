#version 330 core

out vec4 FragColor;

in vec3 crntPos;
in vec3 Normal;
in vec3 color;

uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 camPos;

vec4 direcLight()
{
	float ambient = 0.50f;

	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(vec3(1.5f, 1.0f, 0.5f));
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	float specularLight = 0.50f;
	vec3 viewDirection = normalize(camPos - crntPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
	float specular = specAmount * specularLight;

	return (diffuse + ambient + specular) * lightColor;
}

void main()
{
	FragColor = direcLight() * vec4(color, 1.0f);

	// FragColor = vec4(color, 1.0f);
}