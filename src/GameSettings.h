#ifndef TYPING_GAME_GAME_SETTINGS_H
#define TYPING_GAME_GAME_SETTINGS_H

#include <SFML/Graphics.hpp>
#include <string>

enum ScreenSize {
    Size800x600,
    Size1024x768,
    Size1280x720,
    Size1366x768,
};

class GameSettings {
public:
    GameSettings();

    bool loadDefaultFont(const std::string& path);
    bool loadGameFont(const std::string& path);
    bool loadBackgroundTexture(const std::string& path);

    ScreenSize getScreenSize() const;
    const sf::Font& getDefaultFont() const;
    const sf::Font& getGameFont() const;
    float getSpeed() const;
    float getSpawnInterval() const;
    int getFontSize() const;
    const sf::Sprite& getBackgroundSprite() const;

    void setScreenSize(ScreenSize size);
    void setSpeed(float speed);
    void setSpawnInterval(float interval);
    void setFontSize(int size);
    void updateBackgroundScale(sf::Vector2u windowSize);

private:
    ScreenSize screenSize;
    sf::Font defaultFont;
    sf::Font gameFont;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    float speed;
    float spawnInterval;
    int fontSize;
};

#endif