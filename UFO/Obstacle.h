#pragma once
#include <SFML/Graphics.hpp>

class Obstacle {
public:
    Obstacle(float startX, float startY, float speed, sf::Texture& texture);  // Constructor
    void update();  // Update the position of the obstacle
    void draw(sf::RenderWindow& window);  // Draw the obstacle
    sf::FloatRect getBounds() const;  // Get the bounding box of the obstacle

private:
    sf::RectangleShape obstacleShape;  // Shape representing the obstacle
    float obstacleSpeed;  // Speed of the obstacle
};

