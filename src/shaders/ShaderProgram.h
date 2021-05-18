#pragma once

#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include <string>


/*
	This abstract class represents a generic shader program.
 */

namespace shaders
{
	class ShaderProgram
	{
	private:
		GLuint programID;
		GLuint vertexShaderID;
		GLuint fragmentShaderID;

	public:
		ShaderProgram(std::string& vertexShader, std::string& fragmentShader);
		virtual ~ShaderProgram() = default;

		// Call this function after making the shaderprogram (sets all the attributes of the shader)
		void init();
		// Call this function before rendering
		void start() const;
		// Call this function after rendering
		void stop() const;
		// Call this function when closing the application
		void cleanUp() const;

	protected:
		// Set the inputs of the vertex shader
		virtual void setAttributes() const = 0;
		void setAttribute(const GLuint attribute, const char* variableName) const;

		// Loads value's (uniform variables) into the shader
		void loadFloat(GLuint location, GLfloat value) const;
		void loadVector(GLuint location, glm::vec3 vector) const;
		void loadMatrix(GLuint location, glm::mat4 matrix) const;
		
		virtual void getAllUniformLocations() = 0;
		GLuint getUniformLocation(const GLchar* uniformName) const;
	
	private:
		GLuint loadShader(const std::string& shaderString, GLuint type) const;
		//std::string readFromFile(const std::string& file) const;
	};
}