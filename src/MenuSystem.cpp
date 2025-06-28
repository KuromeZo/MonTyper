#include "MenuSystem.h"
#include <iostream>
#include <vector>
#include <utility>
#include <filesystem>

MenuSystem::MenuSystem(sf::RenderWindow& window, GameSettings& settings)
        : window(window), settings(settings),
          baseWidth(800.0f), baseHeight(600.0f) {  // Базовые размеры для масштабирования
}

void MenuSystem::createMenuText(sf::Text& text, const std::string& string,
                                float posX, float posY, unsigned int size) {
    text.setFont(settings.getDefaultFont());
    text.setString(string);
    text.setCharacterSize(size);
    text.setFillColor(sf::Color::White);

    // Масштабируем позиции в зависимости от текущего размера окна
    float scaleX = window.getSize().x / baseWidth;
    float scaleY = window.getSize().y / baseHeight;

    text.setPosition(posX * scaleX, posY * scaleY);
}

bool MenuSystem::isMouseOverText(const sf::Text& text) {
    // начек позиции мыши
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);
    return text.getGlobalBounds().contains(worldPos);
}

void MenuSystem::showMainMenu() {
    sf::Text newGame, settingsText, exit;

    createMenuText(newGame, "New Game", 350.f, 250.f);
    createMenuText(settingsText, "Settings", 350.f, 300.f);
    createMenuText(exit, "Exit", 350.f, 350.f);

    bool menuOpen = true;

    while (menuOpen && window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::MouseButtonPressed) {
                if (isMouseOverText(newGame)) {
                    return; // Game will be initialized from Game class
                } else if (isMouseOverText(settingsText)) {
                    showSettings();
                    // После изменения размера окна в настройках нужно обновить положение элементов
                    createMenuText(newGame, "New Game", 350.f, 250.f);
                    createMenuText(settingsText, "Settings", 350.f, 300.f);
                    createMenuText(exit, "Exit", 350.f, 350.f);
                } else if (isMouseOverText(exit)) {
                    window.close();
                }
            } else if (event.type == sf::Event::Resized) {
                // Обновляем представление
                sf::FloatRect visibleArea(0.f, 0.f, static_cast<float>(event.size.width), static_cast<float>(event.size.height));
                window.setView(sf::View(visibleArea));

                // Обновляем масштаб фона
                settings.updateBackgroundScale(window.getSize());

                // Обновляем позиции меню
                createMenuText(newGame, "New Game", 350.f, 250.f);
                createMenuText(settingsText, "Settings", 350.f, 300.f);
                createMenuText(exit, "Exit", 350.f, 350.f);
            }
        }

        window.clear();
        window.draw(settings.getBackgroundSprite());
        window.draw(newGame);
        window.draw(settingsText);
        window.draw(exit);
        window.display();
    }
}

void MenuSystem::showSettings() {
    sf::Text title, windowSize, fonts, speed, amount, size, back;

    createMenuText(title, "Settings", 350.f, 100.f, 48);
    createMenuText(windowSize, "Window size", 350.f, 200.f);
    createMenuText(fonts, "Fonts", 350.f, 250.f);
    createMenuText(speed, "Word speed", 350.f, 300.f);
    createMenuText(amount, "Word amount", 350.f, 350.f);
    createMenuText(size, "Word size", 350.f, 400.f);
    createMenuText(back, "Back", 350.f, 450.f);

    bool settingsOpen = true;

    while (settingsOpen && window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::MouseButtonPressed) {
                if (isMouseOverText(windowSize)) {
                    showResolution();
                    // После изменения размера окна обновляем положение элементов
                    createMenuText(title, "Settings", 350.f, 100.f, 48);
                    createMenuText(windowSize, "Window size", 350.f, 200.f);
                    createMenuText(fonts, "Fonts", 350.f, 250.f);
                    createMenuText(speed, "Word speed", 350.f, 300.f);
                    createMenuText(amount, "Word amount", 350.f, 350.f);
                    createMenuText(size, "Word size", 350.f, 400.f);
                    createMenuText(back, "Back", 350.f, 450.f);
                } else if (isMouseOverText(fonts)) {
                    showFontSelection();
                } else if (isMouseOverText(speed)) {
                    showWordSpeed();
                } else if (isMouseOverText(amount)) {
                    showWordAmount();
                } else if (isMouseOverText(size)) {
                    showWordSize();
                } else if (isMouseOverText(back)) {
                    settingsOpen = false;
                }
            } else if (event.type == sf::Event::Resized) {
                // Обновляем представление
                sf::FloatRect visibleArea(0.f, 0.f, static_cast<float>(event.size.width), static_cast<float>(event.size.height));
                window.setView(sf::View(visibleArea));

                // Обновляем масштаб фона
                settings.updateBackgroundScale(window.getSize());

                // Обновляем позиции меню
                createMenuText(title, "Settings", 350.f, 100.f, 48);
                createMenuText(windowSize, "Window size", 350.f, 200.f);
                createMenuText(fonts, "Fonts", 350.f, 250.f);
                createMenuText(speed, "Word speed", 350.f, 300.f);
                createMenuText(amount, "Word amount", 350.f, 350.f);
                createMenuText(size, "Word size", 350.f, 400.f);
                createMenuText(back, "Back", 350.f, 450.f);
            }
        }

        window.clear();
        window.draw(settings.getBackgroundSprite());
        window.draw(title);
        window.draw(windowSize);
        window.draw(fonts);
        window.draw(speed);
        window.draw(amount);
        window.draw(size);
        window.draw(back);
        window.display();
    }
}

void MenuSystem::showResolution() {
    sf::Text title, back;
    createMenuText(title, "Select Resolution", 250.f, 100.f, 48);
    createMenuText(back, "Back", 350.f, 400.f);

    const std::vector<std::pair<std::string, ScreenSize>> screenSizes = {
            {"800x600", Size800x600},
            {"1024x768", Size1024x768},
            {"1280x720", Size1280x720},
            {"1366x768", Size1366x768},
    };

    std::vector<sf::Text> sizeOptions;
    for (size_t i = 0; i < screenSizes.size(); ++i) {
        sf::Text option;
        createMenuText(option, screenSizes[i].first, 350.f, 200.f + static_cast<float>(i) * 30.f, 20);
        sizeOptions.push_back(option);
    }

    bool settingsOpen = true;

    while (settingsOpen && window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::MouseButtonPressed) {
                if (isMouseOverText(back)) {
                    settingsOpen = false;
                }

                for (size_t i = 0; i < sizeOptions.size(); ++i) {
                    if (isMouseOverText(sizeOptions[i])) {
                        settings.setScreenSize(screenSizes[i].second);

                        // Сохраняем текущую позицию окна
                        sf::Vector2i windowPosition = window.getPosition();

                        // Изменяем размер окна
                        switch (settings.getScreenSize()) {
                            case Size800x600:
                                window.setSize(sf::Vector2u(800, 600));
                                break;
                            case Size1024x768:
                                window.setSize(sf::Vector2u(1024, 768));
                                break;
                            case Size1280x720:
                                window.setSize(sf::Vector2u(1280, 720));
                                break;
                            case Size1366x768:
                                window.setSize(sf::Vector2u(1366, 768));
                                break;
                            default:
                                break;
                        }

                        // Сбрасываем представление к новому размеру окна
                        sf::FloatRect visibleArea(0.f, 0.f, static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y));
                        sf::View view(visibleArea);
                        window.setView(view);

                        // Обновляем фон
                        settings.updateBackgroundScale(window.getSize());

                        // Восстанавливаем позицию окна
                        window.setPosition(windowPosition);

                        // Обновляем позиции элементов меню
                        createMenuText(title, "Select Resolution", 250.f, 100.f, 48);
                        createMenuText(back, "Back", 350.f, 400.f);

                        for (size_t j = 0; j < sizeOptions.size(); ++j) {
                            createMenuText(sizeOptions[j], screenSizes[j].first, 350.f, 200.f + static_cast<float>(j) * 30.f, 20);
                        }
                    }
                }
            } else if (event.type == sf::Event::Resized) {
                // Обновляем представление
                sf::FloatRect visibleArea(0.f, 0.f, static_cast<float>(event.size.width), static_cast<float>(event.size.height));
                window.setView(sf::View(visibleArea));

                // Обновляем масштаб фона
                settings.updateBackgroundScale(window.getSize());

                // Обновляем позиции элементов меню
                createMenuText(title, "Select Resolution", 250.f, 100.f, 48);
                createMenuText(back, "Back", 350.f, 400.f);

                for (size_t j = 0; j < sizeOptions.size(); ++j) {
                    createMenuText(sizeOptions[j], screenSizes[j].first, 350.f, 200.f + static_cast<float>(j) * 30.f, 20);
                }
            }
        }

        window.clear();
        window.draw(settings.getBackgroundSprite());
        window.draw(title);
        for (const auto &option : sizeOptions) {
            window.draw(option);
        }
        window.draw(back);
        window.display();
    }
}

void MenuSystem::showFontSelection() {
    sf::Text title, back;
    createMenuText(title, "Select Font", 250.f, 100.f, 48);
    createMenuText(back, "Back", 350.f, 500.f);

    const std::vector<std::pair<std::string, std::string>> fontOptions = {
            {"Arial", "fonts/arial.ttf"},
            {"PlaywriteIS", "fonts/PlaywriteIS.ttf"},
            {"Lora-Italic", "fonts/Lora-Italic.ttf"},
            {"PlaywriteFRModerne", "fonts/PlaywriteFRModerne.ttf"},
            {"PlaywriteNL", "fonts/PlaywriteNL.ttf"},
            {"Tiny", "fonts/Tiny.ttf"},
            {"PlaywritePL", "fonts/PlaywritePL.ttf"},
            {"PlaywriteVN", "fonts/PlaywriteVN.ttf"},
    };

    std::vector<sf::Text> fontButtons;
    sf::Font tempFont;

    for (size_t i = 0; i < fontOptions.size(); ++i) {
        if (!tempFont.loadFromFile(fontOptions[i].second)) {
            std::cout << "Failed to load font from " << fontOptions[i].second << std::endl;
            continue;
        }

        sf::Text option;
        option.setFont(tempFont);
        option.setString(fontOptions[i].first);
        option.setCharacterSize(20);
        option.setFillColor(sf::Color::White);

        // Масштабируем позицию
        float scaleX = window.getSize().x / baseWidth;
        float scaleY = window.getSize().y / baseHeight;
        option.setPosition(350.f * scaleX, (200.f + static_cast<float>(i) * 30.f) * scaleY);

        fontButtons.push_back(option);
    }

    bool fontSelectionOpen = true;

    while (fontSelectionOpen && window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::MouseButtonPressed) {
                if (isMouseOverText(back)) {
                    fontSelectionOpen = false;
                }

                for (size_t i = 0; i < fontButtons.size(); ++i) {
                    if (isMouseOverText(fontButtons[i])) {
                        std::string fontPath = fontOptions[i].second;
                        if (tempFont.loadFromFile(fontPath)) {
                            settings.loadGameFont(fontPath);
                            fontButtons[i].setFont(tempFont);
                        } else {
                            std::cout << "Failed to load font from " << fontPath << std::endl;
                        }
                    }
                }
            } else if (event.type == sf::Event::Resized) {
                // Обновляем представление
                sf::FloatRect visibleArea(0.f, 0.f, static_cast<float>(event.size.width), static_cast<float>(event.size.height));
                window.setView(sf::View(visibleArea));

                // Обновляем масштаб фона
                settings.updateBackgroundScale(window.getSize());

                // Обновляем позиции элементов меню
                createMenuText(title, "Select Font", 250.f, 100.f, 48);
                createMenuText(back, "Back", 350.f, 500.f);

                // Обновляем позиции кнопок
                float scaleX = window.getSize().x / baseWidth;
                float scaleY = window.getSize().y / baseHeight;

                for (size_t i = 0; i < fontButtons.size(); ++i) {
                    fontButtons[i].setPosition(350.f * scaleX, (200.f + static_cast<float>(i) * 30.f) * scaleY);
                }
            }
        }

        window.clear();
        window.draw(settings.getBackgroundSprite());
        window.draw(title);
        for (const auto &button : fontButtons) {
            window.draw(button);
        }
        window.draw(back);
        window.display();
    }
}

void MenuSystem::showWordSpeed() {
    sf::Text title, back;
    createMenuText(title, "Select word speed", 250.f, 100.f, 48);
    createMenuText(back, "Back", 350.f, 400.f);

    const std::vector<std::pair<std::string, float>> speeds = {
            {"Slow speed", 50.0f},
            {"Standard speed", 100.0f},
            {"Fast speed", 150.0f},
    };

    std::vector<sf::Text> speedOptions;
    for (size_t i = 0; i < speeds.size(); ++i) {
        sf::Text option;
        createMenuText(option, speeds[i].first, 350.f, 200.f + static_cast<float>(i) * 50.f);
        speedOptions.push_back(option);
    }

    bool speedSettingsOpen = true;

    while (speedSettingsOpen && window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::MouseButtonPressed) {
                if (isMouseOverText(back)) {
                    speedSettingsOpen = false;
                }

                for (size_t i = 0; i < speedOptions.size(); ++i) {
                    if (isMouseOverText(speedOptions[i])) {
                        settings.setSpeed(speeds[i].second);
                        speedSettingsOpen = false;
                        break;
                    }
                }
            } else if (event.type == sf::Event::Resized) {
                // Обновляем представление
                sf::FloatRect visibleArea(0.f, 0.f, static_cast<float>(event.size.width), static_cast<float>(event.size.height));
                window.setView(sf::View(visibleArea));

                // Обновляем масштаб фона
                settings.updateBackgroundScale(window.getSize());

                // Обновляем позиции элементов меню
                createMenuText(title, "Select word speed", 250.f, 100.f, 48);
                createMenuText(back, "Back", 350.f, 400.f);

                for (size_t i = 0; i < speedOptions.size(); ++i) {
                    createMenuText(speedOptions[i], speeds[i].first, 350.f, 200.f + static_cast<float>(i) * 50.f);
                }
            }
        }

        window.clear();
        window.draw(settings.getBackgroundSprite());
        window.draw(title);
        for (const auto& option : speedOptions) {
            window.draw(option);
        }
        window.draw(back);
        window.display();
    }
}

void MenuSystem::showWordAmount() {
    sf::Text title, back;
    createMenuText(title, "Select word amount", 250.f, 100.f, 48);
    createMenuText(back, "Back", 350.f, 400.f);

    const std::vector<std::pair<std::string, float>> amount = {
            {"Small amount", 3.0f},
            {"Medium amount", 2.0f},
            {"Big amount", 1.0f},
            {"Giant amount", 0.5f},
    };

    std::vector<sf::Text> amountOptions;
    for (size_t i = 0; i < amount.size(); ++i) {
        sf::Text option;
        createMenuText(option, amount[i].first, 350.f, 200.f + static_cast<float>(i) * 50.f);
        amountOptions.push_back(option);
    }

    bool wordAmountSettingsOpen = true;

    while (wordAmountSettingsOpen && window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::MouseButtonPressed) {
                if (isMouseOverText(back)) {
                    wordAmountSettingsOpen = false;
                }

                for (size_t i = 0; i < amountOptions.size(); ++i) {
                    if (isMouseOverText(amountOptions[i])) {
                        settings.setSpawnInterval(amount[i].second);
                        wordAmountSettingsOpen = false;
                        break;
                    }
                }
            } else if (event.type == sf::Event::Resized) {
                // Обновляем представление
                sf::FloatRect visibleArea(0.f, 0.f, static_cast<float>(event.size.width), static_cast<float>(event.size.height));
                window.setView(sf::View(visibleArea));

                // Обновляем масштаб фона
                settings.updateBackgroundScale(window.getSize());

                // Обновляем позиции элементов меню
                createMenuText(title, "Select word amount", 250.f, 100.f, 48);
                createMenuText(back, "Back", 350.f, 400.f);

                for (size_t i = 0; i < amountOptions.size(); ++i) {
                    createMenuText(amountOptions[i], amount[i].first, 350.f, 200.f + static_cast<float>(i) * 50.f);
                }
            }
        }

        window.clear();
        window.draw(settings.getBackgroundSprite());
        window.draw(title);
        for (const auto& option : amountOptions) {
            window.draw(option);
        }
        window.draw(back);
        window.display();
    }
}

void MenuSystem::showWordSize() {
    sf::Text title, back;
    createMenuText(title, "Select word size", 250.f, 50.f, 48);
    createMenuText(back, "Back", 350.f, 450.f);

    const std::vector<std::pair<std::string, int>> size = {
            {"20", 20},
            {"24", 24},
            {"30", 30},
            {"36", 36},
            {"40", 40},
            {"44", 44},
    };

    std::vector<sf::Text> sizeOptions;
    for (size_t i = 0; i < size.size(); ++i) {
        sf::Text option;
        createMenuText(option, size[i].first, 350.f, 150.f + static_cast<float>(i) * 50.f);
        sizeOptions.push_back(option);
    }

    bool wordSizeSettingsOpen = true;

    while (wordSizeSettingsOpen && window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::MouseButtonPressed) {
                if (isMouseOverText(back)) {
                    wordSizeSettingsOpen = false;
                }

                for (size_t i = 0; i < sizeOptions.size(); ++i) {
                    if (isMouseOverText(sizeOptions[i])) {
                        settings.setFontSize(size[i].second);
                        wordSizeSettingsOpen = false;
                        break;
                    }
                }
            } else if (event.type == sf::Event::Resized) {
                // Обновляем представление
                sf::FloatRect visibleArea(0.f, 0.f, static_cast<float>(event.size.width), static_cast<float>(event.size.height));
                window.setView(sf::View(visibleArea));

                // Обновляем масштаб фона
                settings.updateBackgroundScale(window.getSize());

                // Обновляем позиции элементов меню
                createMenuText(title, "Select word size", 250.f, 50.f, 48);
                createMenuText(back, "Back", 350.f, 450.f);

                for (size_t i = 0; i < sizeOptions.size(); ++i) {
                    createMenuText(sizeOptions[i], size[i].first, 350.f, 150.f + static_cast<float>(i) * 50.f);
                }
            }
        }

        window.clear();
        window.draw(settings.getBackgroundSprite());
        window.draw(title);
        for (const auto& option : sizeOptions) {
            window.draw(option);
        }
        window.draw(back);
        window.display();
    }
}