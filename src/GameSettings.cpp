#include "GameSettings.h"
#include <iostream>

GameSettings::GameSettings()
        : screenSize(Size800x600),
          speed(100.0f),
          spawnInterval(2.0f),
          fontSize(24) {
}

bool GameSettings::loadDefaultFont(const std::string& path) {
    if (!defaultFont.loadFromFile(path)) {
        std::cout << "Failed to load default font from " << path << std::endl;
        return false;
    }
    return true;
}

bool GameSettings::loadGameFont(const std::string& path) {
    if (!gameFont.loadFromFile(path)) {
        std::cout << "Failed to load game font from " << path << std::endl;
        return false;
    }
    return true;
}

bool GameSettings::loadBackgroundTexture(const std::string& path) {
    if (!backgroundTexture.loadFromFile(path)) {
        std::cout << "Failed to load background texture from " << path << std::endl;
        return false;
    }
    backgroundSprite.setTexture(backgroundTexture);
    return true;
}

ScreenSize GameSettings::getScreenSize() const {
    return screenSize;
}

const sf::Font& GameSettings::getDefaultFont() const {
    return defaultFont;
}

const sf::Font& GameSettings::getGameFont() const {
    return gameFont;
}

float GameSettings::getSpeed() const {
    return speed;
}

float GameSettings::getSpawnInterval() const {
    return spawnInterval;
}

int GameSettings::getFontSize() const {
    return fontSize;
}

const sf::Sprite& GameSettings::getBackgroundSprite() const {
    return backgroundSprite;
}

void GameSettings::setScreenSize(ScreenSize size) {
    screenSize = size;
}

void GameSettings::setSpeed(float newSpeed) {
    speed = newSpeed;
}

void GameSettings::setSpawnInterval(float interval) {
    spawnInterval = interval;
}

void GameSettings::setFontSize(int size) {
    fontSize = size;
}

void GameSettings::updateBackgroundScale(sf::Vector2u windowSize) {
    sf::Vector2f targetSize(windowSize);
    sf::Vector2f textureSize(backgroundTexture.getSize());
    backgroundSprite.setScale(targetSize.x / textureSize.x, targetSize.y / textureSize.y);
}