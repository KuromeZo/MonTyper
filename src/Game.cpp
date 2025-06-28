#include "Game.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <filesystem>

Game::Game()
    : gameOver(false),
      score(0),
      missedCount(0),
      spawnTimer(0.0f),
      timeSinceStart(0.0f),
      lastSpawnTime(0.0f),
      lastSpawnY(-100.0f),
      firstWordDelay(3.0f),
      menuSystem(nullptr),
      activeWordIndex(-1) {
}

bool Game::initialize() {
    // рандрмные числа
    srand(static_cast<unsigned int>(time(0)));

    // окно
    window.create(sf::VideoMode(800, 600), "Moving Words", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);

    // пути к ресам
    auto executablePath = std::filesystem::current_path();

    // шрифт
    std::string fontPath = "fonts/arial.ttf";
    if (!settings.loadDefaultFont(fontPath)) {
        std::cout << "Failed to load default font! Tried path: " << fontPath << std::endl;
        return false;
    }

    // бэкграунд
    std::string bgPath = "background/back.png";
    if (!settings.loadBackgroundTexture(bgPath)) {
        std::cout << "Failed to load background image! Tried path: " << bgPath << std::endl;
        return false;
    }

    // resize окна
    settings.updateBackgroundScale(window.getSize());

    // инициализация настроек
    menuSystem = new MenuSystem(window, settings);

    // загрузка слов
    std::string wordsPath = "resources/words.txt";
    if (!wordDB.loadFromFile(wordsPath)) {
        std::cout << "Warning: Failed to load words database from: " << wordsPath << std::endl;
        std::cout << "Generating random words instead." << std::endl;
    }

    return true;
}

void Game::run() {
    if (menuSystem == nullptr) {
        std::cout << "Error: MenuSystem not initialized!" << std::endl;
        return;
    }

    bool inMainMenu = true;

    while (window.isOpen()) {
        if (inMainMenu) {
            menuSystem->showMainMenu();
            inMainMenu = false;

            // После изменения размера окна в меню - сбрасываем представление
            sf::FloatRect visibleArea(0.f, 0.f, static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y));
            sf::View view(visibleArea);
            window.setView(view);

            initializeGame();
        }

        processEvents();

        if (!gameOver) {
            float deltaTime = clock.restart().asSeconds();
            update(deltaTime);
            render();
        } else {
            showGameOver();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                inMainMenu = true;
                resetGame();
            }
        }
    }

    delete menuSystem;
}

void Game::initializeGame() {
    // Reset game state
    gameOver = false;
    score = 0;
    missedCount = 0;
    currentWord.clear();
    words.clear();
    activeWordIndex = -1;

    // Reset timers
    spawnTimer = 0.0f;
    timeSinceStart = 0.0f;
    lastSpawnTime = 0.0f;
    lastSpawnY = -100.0f;

    clock.restart();

    // Получаем текущий размер окна для правильного позиционирования
    float windowWidth = static_cast<float>(window.getSize().x);

    // расположение элементов
    if (settings.getGameFont().getInfo().family == "") {
        currentInputText.setFont(settings.getDefaultFont());
        missedText.setFont(settings.getDefaultFont());
        scoreText.setFont(settings.getDefaultFont());
    } else {
        currentInputText.setFont(settings.getGameFont());
        missedText.setFont(settings.getGameFont());
        scoreText.setFont(settings.getGameFont());
    }

    currentInputText.setCharacterSize(24);
    currentInputText.setFillColor(sf::Color::Green);
    currentInputText.setPosition(10.f, 10.f);

    missedText.setCharacterSize(24);
    missedText.setFillColor(sf::Color::Red);
    missedText.setPosition(windowWidth * 0.5f, 10.f); // Позиционируем по центру окна

    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(windowWidth * 0.25f, 10.f); // Позиционируем на 1/4 ширины окна

    // Инициализируем текст счёта при запуске игры
    scoreText.setString("Score: 0");

    // загрузка задника
    std::string bgPath = "background/sky.jpg";
    if (!gameBackgroundTexture.loadFromFile(bgPath)) {
        std::cout << "Failed to load game background image! Tried path: " << bgPath << std::endl;
        return;
    }

    gameBackground.setTexture(gameBackgroundTexture);

    // resize бэкграунда
    sf::Vector2f targetSize(window.getSize());
    sf::Vector2f textureSize(gameBackgroundTexture.getSize());
    gameBackground.setScale(targetSize.x / textureSize.x, targetSize.y / textureSize.y);
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        } else if (event.type == sf::Event::TextEntered) {
            if (!gameOver) {
                if (event.text.unicode < 128 && event.text.unicode >= 32) {
                    currentWord += static_cast<wchar_t>(event.text.unicode);
                } else if (event.text.unicode == 8 && !currentWord.empty()) {
                    currentWord.erase(currentWord.size() - 1);
                }
            }
        } else if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape) {
                if (gameOver) {
                    resetGame();
                    return;
                } else {
                    gameOver = true;
                }
            }
        } else if (event.type == sf::Event::Resized) {
            // Обновляем представление при изменении размера окна
            sf::FloatRect visibleArea(0.f, 0.f, static_cast<float>(event.size.width), static_cast<float>(event.size.height));
            sf::View view(visibleArea);
            window.setView(view);

            // Обновляем масштаб фона игры
            sf::Vector2f targetSize(window.getSize());
            sf::Vector2f textureSize(gameBackgroundTexture.getSize());
            gameBackground.setScale(targetSize.x / textureSize.x, targetSize.y / textureSize.y);

            // Обновляем позиции UI элементов пропорционально размеру окна
            float windowWidth = static_cast<float>(window.getSize().x);
            missedText.setPosition(windowWidth * 0.5f, 10.f);
            scoreText.setPosition(windowWidth * 0.25f, 10.f);
        }
    }
}

void Game::update(float deltaTime) {
    // обнволение text of the current input
    currentInputText.setString(currentWord);

    // время апдейт
    timeSinceStart += deltaTime;

    // спавн слова после окна
    if (timeSinceStart >= firstWordDelay) {
        spawnTimer += deltaTime;

        // time to spawn a new word
        if (spawnTimer >= settings.getSpawnInterval()) {
            spawnWord();
        }
    }

    // сброс active word index
    activeWordIndex = -1;

    // Проверка на совпадение)
    for (size_t i = 0; i < words.size(); ++i) {
        auto& word = words[i];

        if (word.getWordString().find(currentWord) == 0) {
            // если совпадение по слову то делаем его активным
            activeWordIndex = i;

            // если введено все правильно
            if (currentWord.size() == word.getWordString().size()) {
                // Remove matched word
                words.erase(words.begin() + i);
                currentWord.clear();
                ++score;
                scoreText.setString("Score: " + std::to_string(score));

                activeWordIndex = -1;
                break;
            }
        }
    }

    // проверка на выход за пределы жкрана
    checkCollisions();

    // update position of all words
    for (auto& word : words) {
        word.update(deltaTime);
    }

    // Update miss counter text
    missedText.setString("Missed: " + std::to_string(missedCount));

    // условия проигрыша
    if (missedCount >= 5) {
        gameOver = true;
    }
}

void Game::spawnWord() {
    float currentTime = timeSinceStart;
    float heightLimit = 0.8f * window.getSize().y;
    float startY = static_cast<float>(rand() % static_cast<int>(heightLimit - 50));

    // после времени или если слова прошли достаточно растояния
    if (currentTime - lastSpawnTime >= 1.0f || std::abs(startY - lastSpawnY) > 50.0f) {
        spawnTimer = 0.0f;

        // Get word from database or generate random word if database not loaded
        std::string newWord;
        if (wordDB.isDataLoaded()) {
            newWord = wordDB.getRandomWord();
        } else {
            // если нет базы слов, то генерация
            int wordLength = rand() % 6 + 4;
            for (int i = 0; i < wordLength; ++i) {
                char randomChar = 'a' + rand() % 26;
                newWord += randomChar;
            }
        }

        // Add new word to vector
        float startX = static_cast<float>(window.getSize().x);
        words.emplace_back(newWord, settings.getGameFont().getInfo().family == "" ?
                          settings.getDefaultFont() : settings.getGameFont(),
                          startX, startY, settings.getSpeed(), settings.getFontSize());

        lastSpawnTime = currentTime;
        lastSpawnY = startY;
    }
}

void Game::checkCollisions() {
    // remove words that are off-screen
    words.erase(std::remove_if(words.begin(), words.end(),
                             [&](const MovingWord& word) {
                                 if (word.getText().getPosition().x +
                                     word.getText().getGlobalBounds().width < 0) {
                                     ++missedCount;
                                     return true;
                                 }
                                 return false;
                             }), words.end());
}

void Game::render() {
    window.clear();

    window.draw(gameBackground);

    // отображение всех слов
    for (size_t i = 0; i < words.size(); ++i) {
        // если активное слово то выделяем
        if (static_cast<int>(i) == activeWordIndex) {
            // cxreate a highlighted version of the current word
            sf::Text highlightedText = words[i].getText();

            // set bright color for the active word
            highlightedText.setFillColor(sf::Color::Yellow);

            // Draw the highlighted text behind the normal text
            window.draw(highlightedText);

            // отображение совпадающей части в другом цвете
            if (!currentWord.empty()) {
                sf::Text matchedPart = words[i].getText();
                std::wstring matchedText = currentWord;
                matchedPart.setString(matchedText);
                matchedPart.setFillColor(sf::Color::Green);
                window.draw(matchedPart);
            }
        } else {
            // или draw it normally
            window.draw(words[i].getText());
        }
    }

    // UI elements
    window.draw(currentInputText);
    window.draw(missedText);
    window.draw(scoreText);

    window.display();
}

void Game::showGameOver() {
    sf::Text endGameText;

    if (settings.getGameFont().getInfo().family == "") {
        endGameText.setFont(settings.getDefaultFont());
    } else {
        endGameText.setFont(settings.getGameFont());
    }

    endGameText.setCharacterSize(48);
    endGameText.setFillColor(sf::Color::White);
    endGameText.setString("Game Over! Score: " + std::to_string(score) + "\nPress ESC to continue");

    // Center the text
    sf::FloatRect textRect = endGameText.getLocalBounds();
    endGameText.setOrigin(textRect.width / 2, textRect.height / 2);
    endGameText.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);

    window.clear();
    window.draw(gameBackground);
    window.draw(endGameText);
    window.display();
}

void Game::resetGame() {
    gameOver = false;
    score = 0;
    missedCount = 0;
    currentWord.clear();
    words.clear();
    spawnTimer = 0.0f;
    timeSinceStart = 0.0f;
    activeWordIndex = -1;

    // Обновляем текст счёта при сбросе игры
    scoreText.setString("Score: 0");

    // Обновляем позиции UI к текущему размеру окна
    float windowWidth = static_cast<float>(window.getSize().x);
    missedText.setPosition(windowWidth * 0.5f, 10.f);
    scoreText.setPosition(windowWidth * 0.25f, 10.f);
}