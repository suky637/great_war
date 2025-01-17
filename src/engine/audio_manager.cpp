#include "engine/audio_manager.h"

AudioManager::AudioManager() {
    button_click_buffer.loadFromFile("ressources/audio/button_click.wav");
    button_click.setBuffer(button_click_buffer);
    button_hold_buffer.loadFromFile("ressources/audio/button_hover.wav");
    button_hold.setBuffer(button_hold_buffer);
}

void AudioManager::PlayButtonClick() {
    button_click.setPitch((rand() % 20) / 40.f + 0.75f);
    button_click.play();
}

void AudioManager::PlayButtonHold() {
    button_hold.setPitch((rand() % 20) / 40.f + 0.5f);
    button_hold.play();
}

AudioManager AudioManager::instance;