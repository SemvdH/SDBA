#version 400 core
// The VertexShader is run for each vertex on the screen.


// Position of the vertex
in vec3 position;
// Coordinates of the texture
in vec2 textureCoords;

// Equal to the textureCoords
out vec2 passTextureCoords;

uniform mat4 modelMatrix;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;


void main(void)
{
	// Tell OpenGL where to render the vertex
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position, 1.0);

	// Pass the textureCoords directly to the fragment shader
	passTextureCoords = textureCoords;
}