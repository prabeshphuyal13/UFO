#include "MovingBackground.h"

// Constructor: Initializes the moving background
MovingBackground::MovingBackground(const std::string& textureFile, float speed, int segmentWidth, sf::RenderWindow& window)
    : speed(speed), segmentWidth(segmentWidth) {
    // Load the texture
    if (!bgTexture.loadFromFile(textureFile)) {
        throw std::runtime_error("Failed to load background texture from " + textureFile);
    }

    // Calculate the number of segments needed
    int numSegments = (window.getSize().x / segmentWidth) + 2;

    // Create segments
    for (int i = 0; i < numSegments; ++i) {
        sf::Sprite segment(bgTexture);
        segment.setTextureRect(sf::IntRect(0, 0, segmentWidth, bgTexture.getSize().y));
        segment.setPosition(static_cast<float>(i * segmentWidth), 150.f);
        segments.push_back(segment);
    }
}

// Update: Move the segments and reset positions as needed
void MovingBackground::update() {
    for (auto& segment : segments) {
        segment.move(-speed, 0.f); // Move the segment left

        // Reset the segment to the right if it moves off-screen
        if (segment.getPosition().x + segmentWidth < 0) {
            segment.setPosition(segment.getPosition().x + segmentWidth * segments.size(), segment.getPosition().y);
        }
    }
}

// Draw: Render all segments to the window
void MovingBackground::draw(sf::RenderWindow& window) {
    for (const auto& segment : segments) {
        window.draw(segment);
    }
}

// Set the speed of background movement
void MovingBackground::setSpeed(float newSpeed) {
    speed = newSpeed;
}
