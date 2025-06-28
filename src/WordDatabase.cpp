#include "WordDatabase.h"
#include <fstream>
#include <iostream>
#include <random>
#include <algorithm>

WordDatabase::WordDatabase() : isLoaded(false) {
}

bool WordDatabase::loadFromFile(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open words database file: " << filePath << std::endl;
        return false;
    }

    words.clear();
    std::string word;
    while (std::getline(file, word)) {
        // пропуск пустых линий, пробелов и тд
        if (word.empty()) continue;
        
        // Remove leading/trailing whitespace
        word.erase(0, word.find_first_not_of(" \t\n\r\f\v"));
        word.erase(word.find_last_not_of(" \t\n\r\f\v") + 1);
        
        if (!word.empty()) {
            words.push_back(word);
        }
    }

    if (words.empty()) {
        std::cerr << "Error: No words found in the database file!" << std::endl;
        return false;
    }

    isLoaded = true;
    std::cout << "Successfully loaded " << words.size() << " words from database." << std::endl;
    return true;
}

std::string WordDatabase::getRandomWord() {
    if (words.empty()) {
        return "error"; //  error если нет слов
    }

    static std::random_device rd;
    static std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distribution(0, words.size() - 1);
    
    return words[distribution(generator)];
}

bool WordDatabase::isDataLoaded() const {
    return isLoaded;
}

size_t WordDatabase::getWordCount() const {
    return words.size();
}