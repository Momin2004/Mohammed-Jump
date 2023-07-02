#include "ModelLoader.h"
#include <fstream>
#include <sstream>
#include <iostream>

ModelData ModelLoader::loadModel(const std::string& filePath)
{
    ModelData modelData;

    std::ifstream file(filePath);
    if (!file)
    {
        std::cout << "Failed to open model file: " << filePath << std::endl;
        return modelData;
    }

    std::string line;
    while (getline(file, line))
    {
        std::istringstream iss(line);
        std::string type;
        iss >> type;

        if (type == "v")
        {
            float x, y, z;
            if (!(iss >> x >> y >> z))
            {
                std::cout << "Invalid vertex data: " << line << std::endl;
                continue;
            }
            modelData.vertices.push_back(glm::vec3(x, y, z));
        }
        else if (type == "vt")
        {
            float u, v;
            if (!(iss >> u >> v))
            {
                std::cout << "Invalid texture coordinate data: " << line << std::endl;
                continue;
            }
            modelData.texCoords.push_back(glm::vec2(u, v));
        }
        else if (type == "vn")
        {
            float nx, ny, nz;
            if (!(iss >> nx >> ny >> nz))
            {
                std::cout << "Invalid normal data: " << line << std::endl;
                continue;
            }
            modelData.normals.push_back(glm::vec3(nx, ny, nz));
        }
        else if (type == "f")
        {
            std::string vertexIndices[3];
            for (int i = 0; i < 3; i++)
                iss >> vertexIndices[i];

            for (int i = 0; i < 3; i++)
            {
                std::istringstream indicesIss(vertexIndices[i]);
                std::string index;
                unsigned int vertexIndex, texCoordIndex, normalIndex;
                getline(indicesIss, index, '/');
                vertexIndex = std::stoi(index);
                getline(indicesIss, index, '/');
                texCoordIndex = std::stoi(index);
                getline(indicesIss, index, '/');
                normalIndex = std::stoi(index);

                // Save vertex indices
                modelData.indices.push_back(vertexIndex - 1); // OBJ indices start from 1
            }
        }
    }

    return modelData;
}