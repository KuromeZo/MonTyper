#ifndef TYPING_GAME_MENU_SYSTEM_H
#define TYPING_GAME_MENU_SYSTEM_H

#include <SFML/Graphics.hpp>
#include "GameSettings.h"

class MenuSystem {
public:
    // Constructor
    MenuSystem(sf::RenderWindow& window, GameSettings& settings);

    void showMainMenu();

    void showSettings();

    void showResolution();

    void showFontSelection();

    void showWordSpeed();

    void showWordAmount();

    void showWordSize();

private:
    sf::RenderWindow& window;
    GameSettings& settings;

    // Базовые размеры для масштабирования
    const float baseWidth;
    const float baseHeight;

    // Helper functions
    void createMenuText(sf::Text& text, const std::string& string,
                        float posX, float posY, unsigned int size = 24);
    bool isMouseOverText(const sf::Text& text);
};

#endif