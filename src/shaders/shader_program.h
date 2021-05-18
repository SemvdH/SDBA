#pragma once

#include <GL/glew.h>
#include <string>


/*
 * This abstract class represents a generic shader program.
 */

namespace shaders
{
	class ShaderProgram
	{
	private:
		GLuint program_id;
		GLuint vertex_shader_id;
		GLuint fragment_shader_id;

	public:
		ShaderProgram(std::string& vertex_shader, std::string& fragment_shader);
		virtual ~ShaderProgram() = default;

		// Call this function after making the shaderprogram (sets all the attributes of the shader)
		void Init();
		// Call this function before rendering
		void Start() const;
		// Call this function after rendering
		void Stop() const;
		// Call this function when closing the application
		void CleanUp() const;

	protected:
		// Set the inputs of the vertex shader
		virtual void SetAttributes() const = 0;
		void SetAttribute(const GLuint attribute, const char* variable_name) const;

		// Loads value's (uniform variables) into the shader
		void LoadFloat(GLuint location, GLfloat value) const;
		void LoadVector(GLuint location, glm::vec3 vector) const;
		void LoadMatrix(GLuint location, glm::mat4 matrix) const;
		
		virtual void GetAllUniformLocations() = 0;
		GLuint GetUniformLocation(const GLchar* uniform_name) const;
	
	private:
		GLuint LoadShader(const std::string& shader_string, GLuint type) const;
	};
}