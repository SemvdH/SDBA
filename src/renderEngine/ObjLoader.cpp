#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <glm/gtc/matrix_transform.hpp>
#include "Loader.h"
#include "ObjLoader.h"

/*
 * Grotendeels van deze functies zijn gemaakt door:
 * https://github.com/Hopson97/ThinMatrix-OpenGL-Engine/blob/master/Source/Render_Engine/OBJLoader.cpp
 */

static void split(const std::string& s, char delim, std::vector<std::string>& elems)
{
    std::stringstream ss;
    ss.str(s);
    std::string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
}

static std::vector<std::string> split(const std::string& s, char delim)
{
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

static void processVertex(const std::vector<std::string>& vertexData,
    const std::vector<glm::vec3>& normals,
    const std::vector<glm::vec2>& textures,
    std::vector<GLuint>& indices,
    std::vector<GLfloat>& textureArray,
    std::vector<GLfloat>& normalArray)
{
    GLuint currentVertexPointer = std::stoi(vertexData.at(0)) - 1;
    indices.push_back(currentVertexPointer);

    glm::vec2 currentTexture = textures.at(std::stoi(vertexData.at(1)) - 1);
    textureArray[(currentVertexPointer * 2) % textureArray.size()] = currentTexture.x;
    textureArray[(currentVertexPointer * 2 + 1) % textureArray.size()] = 1 - currentTexture.y;

    glm::vec3 currentNorm = normals.at(std::stoi(vertexData.at(2)) - 1);
    normalArray[currentVertexPointer * 3] = currentNorm.x;
    normalArray[currentVertexPointer * 3 + 1] = currentNorm.y;
    normalArray[currentVertexPointer * 3 + 2] = currentNorm.z;
}

models::RawModel LoadObjModel(std::string fileName)
{
    std::ifstream inFile (fileName);
    if ( !inFile.is_open() ) 
    {
        throw std::runtime_error ( "Could not open model file " + fileName + ".obj!" );
    }
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> textures;
    std::vector<GLuint> indices;
    std::vector<GLfloat> vertexArray;
    std::vector<GLfloat> normalArray;
    std::vector<GLfloat> textureArray;
    std::string line;
	
    try
    {
        while (std::getline(inFile, line))
        {
            std::vector<std::string> splitline = split(line, ' ');
            if (splitline.at(0) == "v")
            {
                glm::vec3 vertex;
                vertex.x = std::stof(splitline.at(1));
                vertex.y = std::stof(splitline.at(2));
                vertex.z = std::stof(splitline.at(3));
                vertices.push_back(vertex);
            }
            else if (splitline.at(0) == "vt")
            {
                glm::vec2 texture;
                texture.x = std::stof(splitline.at(1));
                texture.y = std::stof(splitline.at(2));
                textures.push_back(texture);
            }
            else if (splitline.at(0) == "vn")
            {
                glm::vec3 normal;
                normal.x = std::stof(splitline.at(1));
                normal.y = std::stof(splitline.at(2));
                normal.z = std::stof(splitline.at(3));
                normals.push_back(normal);
            }
            else if (splitline.at(0) == "f")
            {
                normalArray = std::vector<GLfloat>(vertices.size() * 3);
                textureArray = std::vector<GLfloat>(textures.size() * 2);
                break;
            }
        }
    	
        while (true)
        {
            std::vector<std::string> splitline = split(line, ' ');
            std::vector<std::string> vertex1 = split(splitline.at(1), '/');
            std::vector<std::string> vertex2 = split(splitline.at(2), '/');
            std::vector<std::string> vertex3 = split(splitline.at(3), '/');
            processVertex(vertex1, normals, textures, indices, textureArray, normalArray);
            processVertex(vertex2, normals, textures, indices, textureArray, normalArray);
            processVertex(vertex3, normals, textures, indices, textureArray, normalArray);
            if (!std::getline(inFile, line))
            {
                break;
            }
        }
    } catch (const std::exception& e)
    {
    	// Always go in here
    }

    inFile.close();
	
    vertexArray = std::vector<GLfloat>( vertices.size() * 3 );
    int p = 0;
    for ( auto& vertex : vertices ) 
    {
        vertexArray[p++] = vertex.x;
        vertexArray[p++] = vertex.y;
        vertexArray[p++] = vertex.z;
    }

    return renderEngine::loader::LoadToVAO( vertexArray, textureArray, indices);
}