#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <glm/gtc/matrix_transform.hpp>
#include "loader.h"
#include "obj_loader.h"

namespace render_engine
{
    static void Split(const std::string& s, char delim, std::vector<std::string>& elems)
    {
        std::stringstream ss;
        ss.str(s);
        std::string item;
        while (getline(ss, item, delim)) {
            elems.push_back(item);
        }
    }

    static std::vector<std::string> Split(const std::string& s, char delim)
    {
        std::vector<std::string> elems;
        Split(s, delim, elems);
        return elems;
    }

    static void ProcessVertex(const std::vector<std::string>& vertex_data,
        const std::vector<glm::vec3>& normals,
        const std::vector<glm::vec2>& textures,
        std::vector<GLuint>& indices,
        std::vector<GLfloat>& texture_array,
        std::vector<GLfloat>& normal_array)
    {
        GLuint current_vertex_pointer = std::stoi(vertex_data.at(0)) - 1;
        indices.push_back(current_vertex_pointer);

        glm::vec2 current_texture = textures.at(std::stoi(vertex_data.at(1)) - 1);
        texture_array[(current_vertex_pointer * 2) % texture_array.size()] = current_texture.x;
        texture_array[(current_vertex_pointer * 2 + 1) % texture_array.size()] = 1 - current_texture.y;

        glm::vec3 current_norm = normals.at(std::stoi(vertex_data.at(2)) - 1);
        normal_array[current_vertex_pointer * 3] = current_norm.x;
        normal_array[current_vertex_pointer * 3 + 1] = current_norm.y;
        normal_array[current_vertex_pointer * 3 + 2] = current_norm.z;
    }

    models::RawModel LoadObjModel(std::string file_name)
    {
        std::ifstream inFile(file_name);
        if (!inFile.is_open())
        {
            throw std::runtime_error("Could not open model file " + file_name + ".obj!");
        }
        std::vector<glm::vec3> vertices;
        std::vector<glm::vec3> normals;
        std::vector<glm::vec2> textures;
        std::vector<GLuint> indices;
        std::vector<GLfloat> vertex_array;
        std::vector<GLfloat> normal_array;
        std::vector<GLfloat> texture_array;
        std::string line;

        try
        {
            while (std::getline(inFile, line))
            {
                std::vector<std::string> split_line = Split(line, ' ');
                if (split_line.at(0) == "v")
                {
                    glm::vec3 vertex;
                    vertex.x = std::stof(split_line.at(1));
                    vertex.y = std::stof(split_line.at(2));
                    vertex.z = std::stof(split_line.at(3));
                    vertices.push_back(vertex);
                }
                else if (split_line.at(0) == "vt")
                {
                    glm::vec2 texture;
                    texture.x = std::stof(split_line.at(1));
                    texture.y = std::stof(split_line.at(2));
                    textures.push_back(texture);
                }
                else if (split_line.at(0) == "vn")
                {
                    glm::vec3 normal;
                    normal.x = std::stof(split_line.at(1));
                    normal.y = std::stof(split_line.at(2));
                    normal.z = std::stof(split_line.at(3));
                    normals.push_back(normal);
                }
                else if (split_line.at(0) == "f")
                {
                    normal_array = std::vector<GLfloat>(vertices.size() * 3);
                    texture_array = std::vector<GLfloat>(textures.size() * 2);
                    break;
                }
            }

            while (true)
            {
                std::vector<std::string> split = Split(line, ' ');
                std::vector<std::string> vertex1 = Split(split.at(1), '/');
                std::vector<std::string> vertex2 = Split(split.at(2), '/');
                std::vector<std::string> vertex3 = Split(split.at(3), '/');
                ProcessVertex(vertex1, normals, textures, indices, texture_array, normal_array);
                ProcessVertex(vertex2, normals, textures, indices, texture_array, normal_array);
                ProcessVertex(vertex3, normals, textures, indices, texture_array, normal_array);
                if (!std::getline(inFile, line))
                {
                    break;
                }
            }
        }
        catch (const std::exception& e)
        {
            // Always go in here
        }

        inFile.close();

        vertex_array = std::vector<GLfloat>(vertices.size() * 3);
        int p = 0;
        for (auto& vertex : vertices)
        {
            vertex_array[p++] = vertex.x;
            vertex_array[p++] = vertex.y;
            vertex_array[p++] = vertex.z;
        }

        return render_engine::loader::LoadToVAO(vertex_array, texture_array, normal_array, indices);
    }
}