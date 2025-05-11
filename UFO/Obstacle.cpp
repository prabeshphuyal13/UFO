#include "Obstacle.h"

Obstacle::Obstacle(float startX, float startY, float speed, sf::Texture& texture) : obstacleSpeed(speed) {
    // Initialize obstacle shape 
    obstacleShape.setSize(sf::Vector2f(80.f, 40.f));  // Width, Height
    obstacleShape.setPosition(startX, startY);  // Initial position

    // Apply the texture to the obstacle shape
    obstacleShape.setTexture(&texture);
}

void Obstacle::update() {
    // Move the obstacle to the left
    obstacleShape.move(-obstacleSpeed, 0.f);
}

void Obstacle::draw(sf::RenderWindow& window) {
    window.draw(obstacleShape);  // Draw the obstacle on the window
}

sf::FloatRect Obstacle::getBounds() const {
    return obstacleShape.getGlobalBounds();  // Get the bounding box of the obstacle
}
