#include "Object.h"

Object::Object(const glm::vec3& pos, const glm::vec3& rot, const glm::vec3& scl)
    : position(pos), rotation(rot), scale(scl) {}

void Object::update(float deltaTime) {
    // Implement object-specific update logic here
}

void Object::render() {
    // Implement object-specific rendering logic here
}

void Object::setPosition(const glm::vec3& pos) {
    position = pos;
}

glm::vec3 Object::getPosition() const {
    return position;
}

void Object::setRotation(const glm::vec3& rot) {
    rotation = rot;
}

glm::vec3 Object::getRotation() const {
    return rotation;
}

void Object::setScale(const glm::vec3& scl) {
    scale = scl;
}

glm::vec3 Object::getScale() const {
    return scale;
}