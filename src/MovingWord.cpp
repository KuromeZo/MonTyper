#include "MovingWord.h"

MovingWord::MovingWord(const std::string& word, const sf::Font& font, float x, float y, float speed,
                       unsigned int fontSize) : speed(speed) {
    text.setFont(font);
    text.setString(word);
    text.setFillColor(sf::Color::White);
    text.setPosition({x, y});
    text.setCharacterSize(fontSize);
}

void MovingWord::update(float deltaTime) {
    text.move({-speed * deltaTime, 0});
}

const sf::Text& MovingWord::getText() const {
    return text;
}

std::wstring MovingWord::getWordString() const {
    return text.getString().toWideString();
}