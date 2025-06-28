#ifndef TYPING_GAME_WORD_DATABASE_H
#define TYPING_GAME_WORD_DATABASE_H

#include <string>
#include <vector>

class WordDatabase {
public:
    // Constructor
    WordDatabase();

    bool loadFromFile(const std::string& filePath);

    std::string getRandomWord();

    bool isDataLoaded() const;

    size_t getWordCount() const;

private:
    std::vector<std::string> words;
    bool isLoaded;
};

#endif