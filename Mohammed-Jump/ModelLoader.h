#pragma once

#include <string>
#include <vector>
#include <glm/glm.hpp>

struct ModelData
{
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> texCoords;
    std::vector<glm::vec3> normals;
    std::vector<unsigned int> indices;
};

class ModelLoader
{
public:
    static ModelData loadModel(const std::string& filePath);
};