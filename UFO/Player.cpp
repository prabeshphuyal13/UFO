#include "Player.h"

Player::Player(float startX, float startY, float speed, sf::Texture& texture) : playerSpeed(speed) {

    // Initialize player shape
    playerShape.setSize(sf::Vector2f(150.f, 100.f)); // Width, Height
    playerShape.setOrigin(sf::Vector2f(75, 50)); // Set origin of playerShape 
    playerShape.setPosition(startX, startY);  // Initial position
    stX = startX;
    stY = startY;

    // Apply the texture to the player shape
    playerShape.setTexture(&texture);

    //adjust the texture rectangle to ensure it fits the player shape
    playerShape.setTextureRect(sf::IntRect(0, 0, texture.getSize().x, texture.getSize().y));
}
void Player::setPosition() {
    playerShape.setPosition(stX, stY);  // Initial position
}

void Player::handleInput() {
    // Move up
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        playerShape.move(0.f, -playerSpeed);
    }

    // Move down
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        playerShape.move(0.f, playerSpeed);
    }
}

void Player::update(sf::RenderWindow& window) {
    // Get player position
    sf::Vector2f position = playerShape.getPosition();

    // Get window size
    sf::Vector2u windowSize = window.getSize();

    // Boundary checks
    if (position.y < 155) {
        playerShape.setPosition(position.x, 155);  // Prevent going above the window
    }
    if (position.y > window.getSize().y - 155) {
        playerShape.setPosition(position.x, window.getSize().y - 155);  // Prevent going below the window
    }
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(playerShape);  // Draw the player on the window
}

sf::FloatRect Player::getBounds() const {
    return playerShape.getGlobalBounds();  // Get the bounding box of the player
}