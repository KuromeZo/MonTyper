#ifndef TYPING_GAME_MOVING_WORD_H
#define TYPING_GAME_MOVING_WORD_H

#include <SFML/Graphics.hpp>
#include <string>

class MovingWord {
public:
    // Constructor
    MovingWord(const std::string& word, const sf::Font& font, float x, float y, float speed,
               unsigned int fontSize);

    // Update word position based on time
    void update(float deltaTime);

    // get the text object текст как объект
    const sf::Text& getText() const;

    // get the word string текст как строка
    std::wstring getWordString() const;

private:
    sf::Text text;
    float speed;
};

#endif