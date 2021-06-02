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

		/*
		 * @brief: Call this function after making the shaderprogram (sets all the attributes of the shader)
		 */
		void Init();

		/*
		 * @brief: Call this function before rendering
		 */
		void Start() const;

		/*
		 * @brief: Call this function after rendering
		 */
		void Stop() const;
		
		/*
		 * @brief: Call this function when closing the application
		 */
		void CleanUp() const;

	protected:
		/*
		 * @brief: Set the inputs of the vertex shader
		 */
		virtual void SetAttributes() const = 0;

		/*
		 * @brief: Sets/binds a input variable (in) to a VBO from the model
		 *
		 * @param attribute: The id of the VBO
		 * @param variable_name: The name of the "in" variable in the shader
		 */
		void SetAttribute(const GLuint attribute, const char* variable_name) const;

		/*
		 * @brief: This function loads a float value into a uniform variable into the shader
		 *
		 * @param location: The location of the variable in openGL
		 * @param value: The value which will be loaded into the variable
		 */
		void LoadFloat(GLuint location, GLfloat value) const;

		/*
		 * @brief: This function loads a vector value into a uniform variable into the shader
		 *
		 * @param location: The location of the variable in openGL
		 * @param vector: The value which will be loaded into the variable
		 */
		void LoadVector(GLuint location, glm::vec3 vector) const;

		/*
		 * @brief: This function loads a 4x4 matrix value into a uniform variable into the shader
		 *
		 * @param location: The location of the variable in openGL
		 * @param matrix: The value which will be loaded into the variable
		 */
		void LoadMatrix(GLuint location, glm::mat4 matrix) const;

		/*
		 * @brief: This function will get all the locations of each uniform variable
		 */
		virtual void GetAllUniformLocations() = 0;

		/*
		 * @brief: This function will retrieve the location of a uniform variable
		 *
		 * @param uniform_name: The name of the uniform variable
		 *
		 * @return: The location of the uniform variable
		 */
		GLuint GetUniformLocation(const GLchar* uniform_name) const;
	
	private:
		/*
		 * @brief: This function will load a shader into openGL
		 *
		 * @param shader_string: The shader as a string (the whole code)
		 * @param type: The type of the shader (Vertex/Fragment)
		 *
		 * @return: The id of the shader given by openGL
		 */
		GLuint LoadShader(const std::string& shader_string, GLuint type) const;
	};
}