#include <glm/glm.hpp>
#include "ModelLoader.h"
#include "TextureLoader.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class User
{
public:
    User(const std::string& modelFilePath, const std::string& textureFilePath);
    ~User();

    void render();

private:
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;
    unsigned int textureID;
    unsigned int vertexCount;

    void setupMesh(const ModelData& modelData);
};