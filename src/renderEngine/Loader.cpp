#include <GL/glew.h>
#include <glm/vec3.hpp>
#include "../stb_image.h"
#include "loader.h"

#include <iostream>

namespace render_engine
{
	namespace loader
	{
		static GLuint CreateVao();
		static void StoreDataInAttributeList(int attribute_number, int coordinate_size, std::vector<float>& data);
		static void BindIndicesBuffer(std::vector<unsigned int>& indices);
		static glm::vec3 GetSizeModel(std::vector<float>& positions);

		static std::vector<GLuint> vaos;
		static std::vector<GLuint> vbos;
		static std::vector<GLuint> textures;

		/*
			This function will generate a Model from vertex positions, textureCoordinates and indices.
		*/
		models::RawModel LoadToVAO(std::vector<float>& positions, std::vector<float>& texture_coords, std::vector<float>& normals, std::vector<unsigned int>& indices)
		{
			const GLuint vao_id = CreateVao();
			BindIndicesBuffer(indices);
			StoreDataInAttributeList(0, 3, positions);
			StoreDataInAttributeList(1, 2, texture_coords);
			StoreDataInAttributeList(2, 3, normals);
			glBindVertexArray(0);
			
			const glm::vec3 model_size = GetSizeModel(positions);
			
			return { vao_id, static_cast<int>(indices.size()), model_size };
		}

		/*
			Loads an image as texture into openGL
		 */
		GLuint LoadTexture(std::string file_name)
		{
			int width, height, bpp;
			unsigned char* imgData = stbi_load(file_name.c_str(), &width, &height, &bpp, 4);

			GLuint texture_id;
			glGenTextures(1, &texture_id);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, texture_id);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imgData);

			// Set mipmapping with a constant LOD
			glGenerateMipmap(GL_TEXTURE_2D);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -0.4f);

			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			
			stbi_image_free(imgData);
			textures.push_back(texture_id);
			return texture_id;
		}

		/*
			This function will delete all the vectors declared at the top of this file from openGL.
		*/
		void CleanUp()
		{
			glDeleteVertexArrays(static_cast<GLsizei>(vaos.size()), &vaos[0]);
			glDeleteBuffers(static_cast<GLsizei>(vbos.size()), &vbos[0]);
			glDeleteTextures(static_cast<GLsizei>(textures.size()), &textures[0]);
		}

		/*
			This function will create a new VAO for a new mesh.
		*/
		static GLuint CreateVao()
		{
			GLuint vao_id;
			glGenVertexArrays(1, &vao_id);
			vaos.push_back(vao_id);
			glBindVertexArray(vao_id);
			return vao_id;
		}

		/*
			This function can store data (vbo) in a vao.
		*/
		static void StoreDataInAttributeList(int attribute_number, int coordinate_size, std::vector<float>& data)
		{
			GLuint vbo_id;
			glGenBuffers(1, &vbo_id);
			vbos.push_back(vbo_id);
			glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * data.size(), &data[0], GL_STATIC_DRAW);
			glVertexAttribPointer(attribute_number, coordinate_size, GL_FLOAT, GL_FALSE, 0, 0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		/*
			This functions loads a indices buffer and binds it to a vao.
			(Using this method of rendering is way more effici�nt with large/complex meshes.
			This way you won't have to specify double or more occuring vertices. You just use sort of a lookup table
			to choose which vertex to get)

			Example:
				std::vector<float> vertices =
				{
				  -0.5f, 0.5f, 0,
				  -0.5f, -0.5f, 0,
				  0.5f, -0.5f, 0,
				  0.5f, 0.5f, 0
				};

				std::vector<int> indices =
				{
					0,1,3,
					3,1,2
				};
		*/
		static void BindIndicesBuffer(std::vector<unsigned int>& indices)
		{
			GLuint vbo_id;
			glGenBuffers(1, &vbo_id);
			vbos.push_back(vbo_id);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_id);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * indices.size(), &indices[0], GL_STATIC_DRAW);
		}

		/**
		* @brief gets the width, height and depth of a model
		* @param positions all the points of a model
		* @returns vec3<float> the size values of a model (width, height and depth)
		**/
		static glm::vec3 GetSizeModel(std::vector<float>& positions)
		{
			float minX = 100;
			float maxX = -100;

			float minY = 100;
			float maxY = -100;

			float minZ = 100;
			float maxZ = -100;
			
			for (int i = 0; i < positions.size(); ++i)
			{
				const int index = i % 3;
				const float value = positions[i];
				
				switch (index)
				{
				case 0: // x
					{
						if (value < minX)
						{
							minX = value;
						} else if (value > maxX)
						{
							maxX = value;
						}
						break;
					}
				case 1: // y
					{
						if (value < minY)
						{
							minY = value;
						}
						else if (value > maxY)
						{
							maxY = value;
						}
						break;
					}
				case 2: // z
				{
					if (value < minZ)
					{
						minZ = value;
					}
					else if (value > maxZ)
					{
						maxZ = value;
					}
					break;
				}
				}
			}

			const float sizeX = maxX - minX;
			const float sizeY = maxY - minY;
			const float sizeZ = maxZ - minZ;
			return { sizeX, sizeY, sizeZ };
		}
	}
}
