#include "gui_shader.h"

namespace shaders
{
	static std::string vertex_shader = R"(
	#version 140

	in vec2 position;

	out vec2 texture_coords;

	uniform mat4 model_matrix;

	void main(void)
	{
		gl_Position = model_matrix * vec4(position, 0.0, 1.0);
	
		// This makes top left corner coordinate (0, 0) and bottom right (1, 1)
		texture_coords = vec2((position.x + 1.0) / 2.0, 1 - (position.y + 1.0) / 2.0);
	}
	)";


	static std::string fragment_shader = R"(
	#version 140

	in vec2 texture_coords;

	out vec4 out_color;

	uniform sampler2D gui_texture;

	void main(void)
	{
		out_color = texture(gui_texture, texture_coords);
	}
	)";

	
	GuiShader::GuiShader() : ShaderProgram(vertex_shader, fragment_shader)
	{ }

	void GuiShader::LoadModelMatrix(const glm::mat4& matrix) const
	{
		LoadMatrix(location_model_matrix, matrix);
	}

	void GuiShader::SetAttributes() const
	{
		SetAttribute(0, "position");
	}

	void GuiShader::GetAllUniformLocations()
	{
		location_model_matrix = GetUniformLocation("model_matrix");
	}
}
