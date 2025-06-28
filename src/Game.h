#ifndef TYPING_GAME_GAME_H
#define TYPING_GAME_GAME_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "MovingWord.h"
#include "GameSettings.h"
#include "MenuSystem.h"
#include "WordDatabase.h"

class Game {
public:
    // Constructor
    Game();

    bool initialize();

    void run();

private:
    sf::RenderWindow window;
    GameSettings settings;
    MenuSystem* menuSystem;
    WordDatabase wordDB;

    // Game state
    bool gameOver;
    int score;
    int missedCount;
    std::wstring currentWord;
    std::vector<MovingWord> words;
    int activeWordIndex;

    // Game UI elements
    sf::Text currentInputText;
    sf::Text missedText;
    sf::Text scoreText;

    // Game background
    sf::Sprite gameBackground;
    sf::Texture gameBackgroundTexture;

    // Game timing
    sf::Clock clock;
    float spawnTimer;
    float timeSinceStart;
    float lastSpawnTime;
    float lastSpawnY;
    float firstWordDelay;

    // Game methods
    void initializeGame();
    void processEvents();
    void update(float deltaTime);
    void render();
    void spawnWord();
    void checkCollisions();
    void resetGame();
    void showGameOver();
};

#endif