#include "Player.h"

Player::Player(const glm::vec3& pos, const glm::vec3& rot, const glm::vec3& scl)
    : Object(pos, rot, scl), movementSpeed(5.0f), jumpForce(7.0f), isJumping(false), isOnGround(true) {}

void Player::update(float deltaTime) {
    applyGravity(deltaTime);
    checkGroundCollision();
}

void Player::move(float offsetX, float offsetY, float offsetZ) {
    position.x += offsetX * movementSpeed;
    position.y += offsetY * movementSpeed;
    position.z += offsetZ * movementSpeed;
}

void Player::jump() {
    if (isOnGround) {
        isJumping = true;
        isOnGround = false;
        // Apply upward force for jumping
        position.y += jumpForce;
    }
}

void Player::applyGravity(float deltaTime) {
    // Simulate gravity effect
    if (!isOnGround && !isJumping) {
        float gravity = 9.8f;  // Gravity acceleration
        float displacement = 0.5f * gravity * deltaTime * deltaTime;  // 0.5 * a * t^2
        position.y -= displacement;
    }
}

void Player::checkGroundCollision() {
    // Check if player is on the ground (e.g., colliding with a platform)
    // Perform collision detection and update isOnGround accordingly
    // ...
}