#include "Sound.h"
#include <iostream>

Sound::Sound() = default;

bool Sound::loadSoundEffect(const std::string& name, const std::string& filePath) {
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile(filePath)) {
        std::cerr << "Error loading sound effect file: " << filePath << std::endl;
        return false;
    }

    soundBuffers[name] = buffer;
    sf::Sound sound;
    sound.setBuffer(soundBuffers[name]);
    soundEffects[name] = sound;

    return true;
}

void Sound::playSoundEffect(const std::string& name) {
    if (soundEffects.find(name) != soundEffects.end()) {
        soundEffects[name].play();
    }
    else {
        std::cerr << "Sound effect not found: " << name << std::endl;
    }
}

bool Sound::loadBackgroundMusic(const std::string& filePath) {
    if (!backgroundMusic.openFromFile(filePath)) {
        std::cerr << "Error loading background music file: " << filePath << std::endl;
        return false;
    }

    return true;
}

void Sound::playBackgroundMusic(bool loop) {
    backgroundMusic.setLoop(loop);
    backgroundMusic.play();
}

void Sound::stopBackgroundMusic() {
    backgroundMusic.stop();
}

