#pragma once
#include <SFML/Graphics.hpp>

class Player {
public:
    Player(float startX, float startY, float speed, sf::Texture& texture);  // Constructor to accept texture
    void handleInput();  // Handle keyboard input
    void update(sf::RenderWindow& window);  // Update player position and ensure boundaries
    void draw(sf::RenderWindow& window);  // Draw the player
    sf::FloatRect getBounds() const;  // Get the bounding box of the player
    void setPosition();

private:

    sf::RectangleShape playerShape;  // Shape representing the player
    float playerSpeed;  // Speed of the player
    float stX, stY;

};

