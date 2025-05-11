#ifndef MOVINGBACKGROUND_H
#define MOVINGBACKGROUND_H

#include <SFML/Graphics.hpp>
#include <vector>

class MovingBackground {
private:
    std::vector<sf::Sprite> segments; // Segments of the background
    sf::Texture bgTexture;           // Texture for the background
    float speed;                     // Speed of background movement
    int segmentWidth;                // Width of each background segment

public:
    // Constructor
    MovingBackground(const std::string& textureFile, float speed, int segmentWidth, sf::RenderWindow& window);

    // Update the background segments
    void update();

    // Draw the background segments
    void draw(sf::RenderWindow& window);

    // Set the speed of the background movement
    void setSpeed(float newSpeed);
};

#endif // MOVINGBACKGROUND_H
