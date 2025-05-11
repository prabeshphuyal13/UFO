#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "Player.h"
#include "Obstacle.h"
#include "Sound.h"
#include "MovingBackground.h"




// Reset player position, score, and clear obstacles
void resetGame(Player& player, std::vector<Obstacle>& obstacles, int& score, int& level, float& spawnObs, sf::Clock& clock) {

    player.setPosition();             // Reset to initial position
    obstacles.clear();                // Remove all obstacles
    score = 0;                        // Reset score
    level = 1;                        // Reset level
    spawnObs = 10.f;                  // Reset obs speed
    clock.restart();                  // Restart the obstacle spawn timer
    
}

// Function to load high score from a file
int loadHighScore(const std::string& filePath) {
    std::ifstream file(filePath);
    int highScore = 0;

    if (file.is_open()) {
        file >> highScore; // Read high score from file
        file.close();
    }
    else {
        std::cout << "No high score file found. Initializing to 0." << std::endl;
    }

    return highScore;
}

//Function to save High score to a file
void saveHighScore(const std::string& filePath, int highScore) {
    std::ofstream file(filePath);

    if (file.is_open()) {
        file << highScore; // Write high score to file
        file.close();
    }
    else {
        std::cerr << "Failed to save high score to file!" << std::endl;
    }
}


int main()
{
    bool isGameOver = false;
    bool isPaused = false;
    bool gameStarted = false;

    //------------------movement control---------------//
    float spawnInterval = 0.8f;  // Time between obstacles spawns in seconds
    float spawnObs = 10.f;  //Speed of obstacles
    float playerSpeed = 10.f; // Speed of player

    // Initialize random seed for genrating obstacle
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    //----------------------Create sound---------------------/
    Sound soundManager;

    // Load sound effects
    if (!soundManager.loadSoundEffect("levelUp", "assets\\levelup.WAV")) return -1;
    if (!soundManager.loadSoundEffect("gameOver", "assets\\hit.WAV")) return -1;
    if (!soundManager.loadSoundEffect("highScore", "assets\\highscoreSFX.WAV")) return -1;

    // Load and play background music
    if (!soundManager.loadBackgroundMusic("assets\\bgmusic.WAV")) return -1;
    soundManager.playBackgroundMusic();


    //---------------Create window---------------------------//
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "UFO", sf::Style::Fullscreen);


    //--------------create background-----------------------//
    sf::Texture bgtexture;
    bgtexture.loadFromFile("assets\\background.png");

    sf::Sprite bgsprite;
    bgsprite.setTexture(bgtexture);

    // Get the size of the window and the image
    sf::Vector2u windowSize = window.getSize();
    sf::Vector2u textureSize = bgtexture.getSize();

    // Calculate scale factors to fit the image to the window
    float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
    float scaleY = static_cast<float>(windowSize.y) / textureSize.y;

    // Apply the scale to the sprite
    bgsprite.setScale(scaleX, scaleY);

    // Create the moving clouds background
    MovingBackground movingClouds("assets/cloud.png", 0.8f, 900, window);



    //----------------Create close btn------------------//
    sf::RectangleShape box(sf::Vector2f(50, 50));  // Size of the box
    box.setPosition(window.getSize().x - box.getSize().x - 30, 25); // Positioned 10 pixels from the right and top

    sf::Texture clsbtn;
    if (!clsbtn.loadFromFile("assets\\cross.png")) // Handles error
    {
        return -1;
    }
    box.setTexture(&clsbtn);
    box.setFillColor(sf::Color::Black);

    //-----------------Game Over Text--------------//
    sf::RectangleShape gameOver(sf::Vector2f(600, 300)); //Size of text
    gameOver.setOrigin(sf::Vector2f(300.f, 150.f));
    gameOver.setPosition(window.getSize().x / 2, window.getSize().y / 2); // Position of text

    sf::Texture gameoverTxt;
    if (!gameoverTxt.loadFromFile("assets\\gameover.png")) // Handles error
    {
        return -1;
    }
    gameOver.setTexture(&gameoverTxt);


    //----------------Create player--------------------//
    sf::Texture playerTex;
    if (!playerTex.loadFromFile("assets\\ufo.png")) // Handles error
    {
        return -1;
    }
    Player player(window.getSize().x-1016.f, window.getSize().y-368.f, playerSpeed, playerTex);


    //-----------------Create obstracle------------------//
    sf::Texture obsTex;
    if (!obsTex.loadFromFile("assets\\arrow.png")) // Handles error
    {
        return -1;
    }
    std::vector<Obstacle> obstacles; // Create a vector to hold obstacles

    sf::Clock clock; // Timer for spawning obstacles


    //--------------------Initialize score, level & high score and font---------------//
    const std::string highScoreFile = "highscore.txt";
    int highScore = loadHighScore(highScoreFile);
    int score = 0;
    int level = 1;
    
 
    sf::Font font;
    if (!font.loadFromFile("assets\\font.ttf")) {
        return -1;
    }

    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setString("Score " + std::to_string(score));
    scoreText.setCharacterSize(30);
    scoreText.setFillColor(sf::Color::White);
    sf::FloatRect scoreBounds = scoreText.getLocalBounds(); // Specific name for bounds
    scoreText.setOrigin(scoreBounds.width / 2.0f, scoreBounds.height / 2.0f);
    scoreText.setPosition(window.getSize().x / 2.0f,20.f);

    sf::Text levelText;
    levelText.setFont(font);
    levelText.setString("Level " + std::to_string(level));
    levelText.setCharacterSize(30);
    levelText.setFillColor(sf::Color::White);
    sf::FloatRect levelBounds = levelText.getLocalBounds(); // Specific name for bounds
    levelText.setOrigin(levelBounds.width / 2.0f, levelBounds.height / 2.0f);
    levelText.setPosition(window.getSize().x / 2.0f, 55.f);

    sf::Text highScoreText;
    highScoreText.setFont(font);
    highScoreText.setString("Best: " + std::to_string(highScore));
    highScoreText.setCharacterSize(15);
    highScoreText.setFillColor(sf::Color::White);
    sf::FloatRect highScoreBounds = highScoreText.getLocalBounds(); // Specific name for bounds
    highScoreText.setOrigin(highScoreBounds.width / 2.0f, highScoreBounds.height / 2.0f);
    highScoreText.setPosition(window.getSize().x / 2.0f, 90.f);

    

    //------------New High Score Text -------------------------//

    sf::RectangleShape HighScore(sf::Vector2f(700, 400)); //Size of text
    HighScore.setOrigin(sf::Vector2f(350.f, 200.f));
    HighScore.setPosition(window.getSize().x/2, window.getSize().y/2); // Position of text

    sf::Texture HighScoreTxt;
    if (!HighScoreTxt.loadFromFile("assets\\Highscore.png")) // Handles error
    {
        return -1;
    }
    HighScore.setTexture(&HighScoreTxt);
  

    //--------------------opeing screen----------------------//
    sf::Texture opnTex;
    opnTex.loadFromFile("assets\\opnimg.png");

    sf::Sprite opnBg;
    opnBg.setTexture(opnTex);

    // Apply the scale to the sprite
    opnBg.setScale(scaleX, scaleY);

    // -----------------Game loop-----------------------//
    while (window.isOpen())
    {
        sf::Event event;

        // Update and draw moving clouds
        movingClouds.update(); // Update cloud movement
        movingClouds.draw(window); // Draw the clouds

  
        while (window.pollEvent(event))
        {
            // Check for mouse click on the red box
            if (event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

                // Check if the click is inside the red box
                if (box.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition)))
                {
                    window.close();
                }
            }

            // Check if the spacebar is pressed to start game
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Space) {
                    if (!gameStarted) {
                        gameStarted = true;  // Start the game when Space is pressed on the opening screen
                    }
                    else if (isGameOver) {
                        resetGame(player, obstacles, score, level, spawnObs, clock); // Reset the game if Space is pressed on the game over screen 
                        isGameOver = false;
                    }
                }
            }
            // Check if the spacebar is pressed when game over to start again
            if (isGameOver && event.key.code == sf::Keyboard::Space) {
                // Reset the game if the player presses Space when game is over
                resetGame(player, obstacles, score, level, spawnObs, clock);
                isGameOver = false;
            }
        }

        if (!gameStarted) {

            // Display the opening screen
            window.draw(opnBg);
            window.draw(box);
            player.draw(window);
            window.display();

            continue;  // Skip the rest of the loop until the game starts
        }

        if (isGameOver) {

            if (score > highScore) {
                highScore = score -10; // Update the high score
                saveHighScore(highScoreFile, highScore); // Save the new high score to file
                highScoreText.setString("Best: " + std::to_string(highScore)); // Update the displayed high score
            }

            window.draw(bgsprite); // Draw background
             movingClouds.draw(window); // Draw the clouds
            window.draw(box); // Draw close btn
            player.draw(window); //Draw player
            for (auto& obstacle : obstacles) // Draw the obstacles
            {
                obstacle.draw(window);
            }
            if (score > highScore) window.draw(HighScore);
            else window.draw(gameOver);
            window.draw(scoreText); // Draw the score
            window.draw(levelText); // Draw the level
            window.draw(highScoreText); // Draw the Highscore
            window.display();
            continue;
        }


        // Handle player input
        player.handleInput();

        // Update player position and ensure boundaries
        player.update(window);

        // Spawn obstacles periodically
        if (clock.getElapsedTime().asSeconds() > spawnInterval)
        {
            float randomY = 200.0f + static_cast<float>(std::rand() % (window.getSize().y - 400));// Generete random height for obstacles 
            obstacles.emplace_back(window.getSize().x, randomY, spawnObs, obsTex);// Generate obstacles in randomY height
            clock.restart();
            scoreText.setString("Score " + std::to_string(score));// Update score
            levelText.setString("Level " + std::to_string(level));// Update score
            score += 10;// Score incease
            if (score % 100 == 0 && score != 0) {
                soundManager.playSoundEffect("levelUp");// Play sound
                level++; // Level up
                spawnObs += 2;
            }
        }
        if (score == highScore+10) {

            soundManager.playSoundEffect("gameOver");// Play sound

        }

        // Update obstacles
        for (auto& obstacle : obstacles)
        {
            obstacle.update();
        }

        // Check for collisions
        for (const auto& obstacle : obstacles)
        {
            if (obstacle.getBounds().intersects(player.getBounds()))
            {
                isGameOver = true;
                soundManager.playSoundEffect("gameOver");// play Sound

                break;
            }
        }

        // Remove obstacles that have moved off the screen
        obstacles.erase(std::remove_if(obstacles.begin(), obstacles.end(),
            [&window](const Obstacle& obstacle)
            {
                return obstacle.getBounds().left + obstacle.getBounds().width < 0;
            }), obstacles.end());


        window.clear();  // Clear the window

        window.draw(bgsprite); //Draw background 

        movingClouds.draw(window); // Moving clouds


        window.draw(scoreText); // Draw the score
        window.draw(levelText); // Draw the level
       
        window.draw(highScoreText); // Draw the Highscore
       
 
        window.draw(box); // Draw close btn

        player.draw(window); // Draw the player

        for (auto& obstacle : obstacles) // Draw the obstacles
        {
            obstacle.draw(window);
        }
        if (score % 100 == 0 && score != 0) {

            soundManager.playSoundEffect("levelUp");// Play sound

        }

        window.setFramerateLimit(60);
        window.display(); //Display Window
    }
    return 0;
}

