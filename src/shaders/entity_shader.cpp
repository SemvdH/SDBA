#include "entity_shader.h"
#include "../toolbox/toolbox.h"
#include <deque>

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
	out vec3 to_light_vector[4];
	out vec3 to_camera_vector;
	out float visibility;

	uniform mat4 model_matrix;
	uniform mat4 projection_matrix;
	uniform mat4 view_matrix;
	uniform vec3 light_position[4];

	const float density = 0.0017;
	const float gradient = 4;
	
	void main(void)
	{
		// Calculate the real position of the vertex (after rotation and scaling)
		vec4 world_position = model_matrix * vec4(position, 1.0);

		vec4 position_rel_to_cam = view_matrix * world_position;
	
		// Tell OpenGL where to render the vertex
		gl_Position = projection_matrix * position_rel_to_cam;

		// Pass the textureCoords directly to the fragment shader
		pass_texture_coords = texture_coords;

		surface_normal = (model_matrix * vec4(normal, 0.0)).xyz;
		for (int i = 0; i < 4; i++)
		{
			to_light_vector[i] = light_position[i] - world_position.xyz;
		}
		to_camera_vector = (inverse(view_matrix) * vec4(0.0, 0.0, 0.0, 1.0)).xyz - world_position.xyz;

		// Calculate the density/visibility of the vertex with the fog
		float distance = length(position_rel_to_cam.xyz);
		visibility = exp(-pow((distance * density), gradient));
		visibility = clamp(visibility, 0.0, 1.0);
	}
	)";
	

	static std::string fragment_shader = R"(
	#version 400 core
	// The FragmentShader is run for each pixel in a face on the screen.


	// Interpolated textureCoordinates of the vertex (relative to the distance to each vertex)
	in vec2 pass_texture_coords;

	in vec3 surface_normal;
	in vec3 to_light_vector[4];
	in vec3 to_camera_vector;
	in float visibility;

	// Final color of the pixel
	out vec4 out_color;

	// The texture of the model
	uniform sampler2D model_texture;

	uniform vec3 light_color[4];
	uniform vec3 attenuation[4];
	uniform float shine_damper;
	uniform float reflectivity;
	uniform vec3 sky_color;

	const float min_diffuse_lighting = 0.1;
	
	void main(void)
	{
		vec3 unit_normal = normalize(surface_normal);
		vec3 unit_camera_vector = normalize(to_camera_vector);

		vec3 total_diffuse = vec3(0.0);
		vec3 total_specular = vec3(0.0);
	
		for (int i = 0; i < 4; i++)
		{
			float distance = length(to_light_vector[i]);
			float att_factor = attenuation[i].x + (attenuation[i].y * distance) + (attenuation[i].z * distance * distance);
	
			vec3 unit_light_vector = normalize(to_light_vector[i]);

			// Calculate the diffuse lighting
			float dot_diffuse = dot(unit_normal, unit_light_vector);
			float brightness = max(dot_diffuse, 0.0);

			// Calculate the specular lighting
			vec3 light_direction = -unit_light_vector;
			vec3 reflected_light_direction = reflect(light_direction, unit_normal);
			float dot_specular = dot(reflected_light_direction, unit_camera_vector);
			dot_specular = max(dot_specular, 0.0);
			float damped_specular = pow(dot_specular, shine_damper);
		
			total_diffuse = total_diffuse + (brightness * light_color[i]) / att_factor;
			total_specular = total_specular + (damped_specular * reflectivity * light_color[i]) / att_factor;
		}

		total_diffuse = max(total_diffuse, min_diffuse_lighting);
	
		out_color = vec4(total_diffuse, 1.0) * texture(model_texture, pass_texture_coords) + vec4(total_specular, 1.0);
		out_color = mix(vec4(sky_color, 1.0), out_color, visibility);
	}
	)";
	
	
	EntityShader::EntityShader(): ShaderProgram(vertex_shader, fragment_shader)
	{ }

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

	void EntityShader::LoadLights(std::vector<entities::Light>& lights) const
	{
		for (int i = 0; i < MAX_LIGHTS; ++i)
		{
			if (i < lights.size())
			{
				LoadVector(location_light_position[i], lights[i].GetPosition());
				LoadVector(location_light_color[i], lights[i].GetColor());
				LoadVector(location_light_attenuation[i], lights[i].GetAttenuation());
			} else
			{
				LoadVector(location_light_position[i], glm::vec3(0, 0, 0));
				LoadVector(location_light_color[i], glm::vec3(0, 0, 0));
				LoadVector(location_light_attenuation[i], glm::vec3(1, 0, 0));
			}
		}
	}

	void EntityShader::LoadLights(std::deque<entities::Light>& lights) const
	{
		for (int i = 0; i < MAX_LIGHTS; ++i)
		{
			if (i < lights.size())
			{
				LoadVector(location_light_position[i], lights[i].GetPosition());
				LoadVector(location_light_color[i], lights[i].GetColor());
				LoadVector(location_light_attenuation[i], lights[i].GetAttenuation());
			}
			else
			{
				LoadVector(location_light_position[i], glm::vec3(0, 0, 0));
				LoadVector(location_light_color[i], glm::vec3(0, 0, 0));
				LoadVector(location_light_attenuation[i], glm::vec3(1, 0, 0));
			}
		}
	}

	void EntityShader::LoadShineVariables(float shine_damper, float reflectivity) const
	{
		LoadFloat(location_shine_damper, shine_damper);
		LoadFloat(location_reflectivity, reflectivity);
	}

	void EntityShader::LoadSkyColor(glm::vec3 sky_color) const
	{
		LoadVector(location_sky_color, sky_color);
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
		location_shine_damper = GetUniformLocation("shine_damper");
		location_reflectivity = GetUniformLocation("reflectivity");
		location_sky_color = GetUniformLocation("sky_color");

		for (int i = 0; i < MAX_LIGHTS; ++i)
		{
			std::string light_pos = std::string("light_position[") + std::to_string(i) + "]";
			location_light_position[i] = GetUniformLocation(light_pos.c_str());

			std::string light_color = std::string("light_color[") + std::to_string(i) + "]";
			location_light_color[i] = GetUniformLocation(light_color.c_str());

			std::string light_attenuation = std::string("attenuation[") + std::to_string(i) + "]";
			location_light_attenuation[i] = GetUniformLocation(light_attenuation.c_str());
		}
	}
}
