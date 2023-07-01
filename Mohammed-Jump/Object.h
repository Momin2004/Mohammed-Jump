#ifndef OBJECT_H
#define OBJECT_H

#include <glm/glm.hpp>

class Object {
protected:
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;

public:
    Object(const glm::vec3& pos = glm::vec3(0.0f), const glm::vec3& rot = glm::vec3(0.0f), const glm::vec3& scl = glm::vec3(1.0f));

    virtual void update(float deltaTime);
    virtual void render();

    // Getters and setters for position, rotation, and scale
    void setPosition(const glm::vec3& pos);
    glm::vec3 getPosition() const;

    void setRotation(const glm::vec3& rot);
    glm::vec3 getRotation() const;

    void setScale(const glm::vec3& scl);
    glm::vec3 getScale() const;
};

#endif  // OBJECT_H
