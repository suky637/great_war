#include "engine/audio_manager.h"

AudioManager::AudioManager() {
    button_click_buffer.loadFromFile("ressources/audio/button_click.wav");
    button_click.setBuffer(button_click_buffer);
}

void AudioManager::PlayButtonClick() {
    button_click.play();
}

AudioManager AudioManager::instance;