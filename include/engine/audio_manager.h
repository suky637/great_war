#include <SFML/Audio.hpp>

class AudioManager {
    public:
    static AudioManager instance;
    AudioManager();
    sf::SoundBuffer button_click_buffer;
    sf::Sound button_click;
    void PlayButtonClick();
};