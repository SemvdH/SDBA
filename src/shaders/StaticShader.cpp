#include "StaticShader.h"
#include "../toolbox/Toolbox.h"

namespace shaders
{
	static std::string vertexShader = R"(
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
	)";
	

	static std::string fragmentShader = R"(
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
	)";
	
	
	StaticShader::StaticShader(): ShaderProgram(vertexShader, fragmentShader)
	{
	}

	void StaticShader::loadModelMatrix(const glm::mat4& matrix) const
	{
		loadMatrix(location_modelMatrix, matrix);
	}

	void StaticShader::loadProjectionMatrix(const glm::mat4& projection) const
	{
		loadMatrix(location_projectionMatrix, projection);
	}

	void StaticShader::loadViewMatrix(entities::Camera& camera) const
	{
		const glm::mat4 viewMatrix = toolbox::createViewMatrix(camera);
		loadMatrix(location_viewMatrix, viewMatrix);
	}

	void StaticShader::setAttributes() const
	{
		setAttribute(0, "position");
		setAttribute(1, "textureCoords");
	}

	void StaticShader::getAllUniformLocations()
	{
		location_modelMatrix = getUniformLocation("modelMatrix");
		location_projectionMatrix = getUniformLocation("projectionMatrix");
		location_viewMatrix = getUniformLocation("viewMatrix");
	}
}
