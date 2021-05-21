#include "entity_shader.h"
#include "../toolbox/toolbox.h"

namespace shaders
{
	static std::string vertex_shader = R"(
	#version 400 core
	// The VertexShader is run for each vertex on the screen.


	// Position of the vertex
	in vec3 position;
	// Coordinates of the texture
	in vec2 texture_coords;
	// The normal of the vertex
	in vec3 normal;

	// Equal to the texture_coords
	out vec2 pass_texture_coords;
	out vec3 surface_normal;
	out vec3 to_light_vector;
	out vec3 to_camera_vector;

	uniform mat4 model_matrix;
	uniform mat4 projection_matrix;
	uniform mat4 view_matrix;
	uniform vec3 light_position;

	void main(void)
	{
		// Calculate the real position of the vertex (after rotation and scaling)
		vec4 world_position = model_matrix * vec4(position, 1.0);
	
		// Tell OpenGL where to render the vertex
		gl_Position = projection_matrix * view_matrix * world_position;

		// Pass the textureCoords directly to the fragment shader
		pass_texture_coords = texture_coords;

		surface_normal = (model_matrix * vec4(normal, 0.0)).xyz;
		to_light_vector = light_position - world_position.xyz;
		to_camera_vector = (inverse(view_matrix) * vec4(0.0, 0.0, 0.0, 1.0)).xyz - world_position.xyz;
	}
	)";
	

	static std::string fragment_shader = R"(
	#version 400 core
	// The FragmentShader is run for each pixel in a face on the screen.


	// Interpolated textureCoordinates of the vertex (relative to the distance to each vertex)
	in vec2 pass_texture_coords;

	in vec3 surface_normal;
	in vec3 to_light_vector;
	in vec3 to_camera_vector;

	// Final color of the pixel
	out vec4 out_color;

	// The texture of the model
	uniform sampler2D texture_sampler;

	uniform vec3 light_color;
	uniform float shine_damper;
	uniform float reflectivity;
	
	void main(void)
	{
		vec3 unit_normal = normalize(surface_normal);
		vec3 unit_light_vector = normalize(to_light_vector);
		vec3 unit_camera_vector = normalize(to_camera_vector); 

		// Calculate the diffuse lighting
		float dot_diffuse = dot(unit_normal, unit_light_vector);
		float brightness = max(dot_diffuse, 0.1);
		vec3 diffuse = brightness * light_color;

		// Calculate the specular lighting
		vec3 light_direction = -unit_light_vector;
		vec3 reflected_light_direction = reflect(light_direction, unit_normal);
		float dot_specular = dot(reflected_light_direction, unit_camera_vector);
		dot_specular = max(dot_specular, 0.0);
		float damped_specular = pow(dot_specular, shine_damper);
		vec3 specular = damped_specular * reflectivity * light_color;
		
		out_color = vec4(diffuse, 1.0) * texture(texture_sampler, pass_texture_coords) + vec4(specular, 1.0);
	}
	)";
	
	
	EntityShader::EntityShader(): ShaderProgram(vertex_shader, fragment_shader)
	{
	}

	void EntityShader::LoadModelMatrix(const glm::mat4& matrix) const
	{
		LoadMatrix(location_model_matrix, matrix);
	}

	void EntityShader::LoadProjectionMatrix(const glm::mat4& projection) const
	{
		LoadMatrix(location_projection_matrix, projection);
	}

	void EntityShader::LoadViewMatrix(entities::Camera& camera) const
	{
		const glm::mat4 view_matrix = toolbox::CreateViewMatrix(camera);
		LoadMatrix(location_view_matrix, view_matrix);
	}

	void EntityShader::LoadLight(entities::Light& light) const
	{
		LoadVector(location_light_position, light.GetPosition());
		LoadVector(location_light_color, light.GetColor());
	}

	void EntityShader::LoadShineVariables(float shine_damper, float reflectivity) const
	{
		LoadFloat(location_shine_damper, shine_damper);
		LoadFloat(location_reflectivity, reflectivity);
	}

	void EntityShader::SetAttributes() const
	{
		// Load the position VBO and textureCoords VBO from the VAO into the shader "in" variables
		SetAttribute(0, "position");
		SetAttribute(1, "texture_coords");
		SetAttribute(2, "normal");
	}

	void EntityShader::GetAllUniformLocations()
	{
		// Get the locations from the uniform variables from the shaders
		location_model_matrix = GetUniformLocation("model_matrix");
		location_projection_matrix = GetUniformLocation("projection_matrix");
		location_view_matrix = GetUniformLocation("view_matrix");
		location_light_position = GetUniformLocation("light_position");
		location_light_color = GetUniformLocation("light_color");
		location_shine_damper = GetUniformLocation("shine_damper");
		location_reflectivity = GetUniformLocation("reflectivity");
	}
}
