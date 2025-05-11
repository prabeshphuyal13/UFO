#ifndef SOUND_H
#define SOUND_H

#include <SFML/Audio.hpp>
#include <string>
#include <map>

class Sound {
public:
    Sound();

    bool loadSoundEffect(const std::string& name, const std::string& filePath);
    void playSoundEffect(const std::string& name);

    bool loadBackgroundMusic(const std::string& filePath);
    void playBackgroundMusic(bool loop = true);
    void stopBackgroundMusic();


private:
    std::map<std::string, sf::SoundBuffer> soundBuffers;
    std::map<std::string, sf::Sound> soundEffects;
    sf::Music backgroundMusic;
};

#endif // SOUND_H
