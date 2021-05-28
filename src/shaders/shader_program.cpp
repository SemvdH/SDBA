#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader_program.h"

namespace shaders
{
	ShaderProgram::ShaderProgram(std::string& vertex_shader, std::string& fragment_shader)
	{
		vertex_shader_id = LoadShader(vertex_shader, GL_VERTEX_SHADER);
		fragment_shader_id = LoadShader(fragment_shader, GL_FRAGMENT_SHADER);
		program_id = glCreateProgram();
		glAttachShader(program_id, vertex_shader_id);
		glAttachShader(program_id, fragment_shader_id);
	}

	void ShaderProgram::Init()
	{
		SetAttributes();
		glLinkProgram(program_id);
		glValidateProgram(program_id);
		GetAllUniformLocations();
	}

	// This method will Start the shaders
	void ShaderProgram::Start() const
	{
		glUseProgram(program_id);
	}

	// This method will Stop the shaders
	void ShaderProgram::Stop() const
	{
		glUseProgram(0);
	}

	// This method will clean up all the shaders
	void ShaderProgram::CleanUp() const
	{
		Stop();
		glDetachShader(program_id, vertex_shader_id);
		glDetachShader(program_id, fragment_shader_id);
		glDeleteShader(vertex_shader_id);
		glDeleteShader(fragment_shader_id);
		glDeleteProgram(program_id);
	}

	// This method sets an input variabele into the shaders
	void ShaderProgram::SetAttribute(const GLuint attribute, const char* variable_name) const
	{
		glBindAttribLocation(program_id, attribute, variable_name);
	}

	void ShaderProgram::LoadFloat(GLuint location, GLfloat value) const
	{
		glUniform1f(location, value);
	}

	void ShaderProgram::LoadVector(GLuint location, glm::vec3 vector) const
	{
		glUniform3fv(location, 1, glm::value_ptr(vector));
	}

	void ShaderProgram::LoadMatrix(GLuint location, glm::mat4 matrix) const
	{
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	GLuint ShaderProgram::GetUniformLocation(const GLchar* uniform_name) const
	{
		return glGetUniformLocation(program_id, uniform_name);
	}

	// This method loads a shader into openGL
	GLuint ShaderProgram::LoadShader(const std::string& shader_string, const GLuint type) const
	{
		const char* shader_text = shader_string.c_str();
		const GLuint shader_id = glCreateShader(type);
		glShaderSource(shader_id, 1, &shader_text, NULL);
		glCompileShader(shader_id);
		
		GLint succes = 0;
		glGetShaderiv(shader_id, GL_COMPILE_STATUS, &succes);
		if (succes == GL_FALSE)
		{
			GLint max_length = 0;
			glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &max_length);

			std::vector<GLchar> error_log(max_length);
			glGetShaderInfoLog(shader_id, max_length, &max_length, &error_log[0]);
			for (std::vector<GLchar>::const_iterator i = error_log.begin(); i != error_log.end(); ++i)
			{
				std::cout << *i;
			}
			std::cout << std::endl;
			std::cerr << "Could not compile shader" << std::endl;
			CleanUp();
			std::exit(-1);
		}

		return shader_id;
	}
}
