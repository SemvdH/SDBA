#version 400 core
// The FragmentShader is run for each pixel in a face on the screen.


// Interpolated textureCoordinates of the vertex (relative to the distance to each vertex)
in vec2 passTextureCoords;

// Final color of the pixel
out vec4 outColor;

// The texture of the model
uniform sampler2D textureSampler;

void main(void)
{
	outColor = texture(textureSampler, passTextureCoords);
}