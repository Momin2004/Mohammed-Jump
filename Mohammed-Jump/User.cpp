#include "User.h"
#include "ModelLoader.h"
#include "TextureLoader.h"

User::User(const std::string& modelFilePath, const std::string& textureFilePath)
{
    ModelData modelData = ModelLoader::loadModel(modelFilePath);
    textureID = TextureLoader::loadTexture(textureFilePath);

    setupMesh(modelData);
}

User::~User()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteTextures(1, &textureID);
}

void User::render()
{
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, vertexCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void User::setupMesh(const ModelData& modelData)
{
    vertexCount = modelData.indices.size();

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, modelData.vertices.size() * sizeof(glm::vec3), &modelData.vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, modelData.indices.size() * sizeof(unsigned int), &modelData.indices[0], GL_STATIC_DRAW);

    // Vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}