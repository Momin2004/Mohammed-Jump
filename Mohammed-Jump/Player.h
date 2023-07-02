#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "Object.h"

class Player : public Object {
private:
    float movementSpeed;
    float jumpForce;
    bool isJumping;
    bool isOnGround;

public:
    Player(const glm::vec3& pos = glm::vec3(0.0f), const glm::vec3& rot = glm::vec3(0.0f), const glm::vec3& scl = glm::vec3(1.0f));

    void update(float deltaTime) override;
    void move(float offsetX, float offsetY, float offsetZ);
    void jump();

private:
    void applyGravity(float deltaTime);
    void checkGroundCollision();
};

#endif  // PLAYER_H


