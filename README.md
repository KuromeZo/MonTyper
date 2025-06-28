# Typing Game

A fast-paced C++ typing game built with SFML where players must type moving words before they disappear off the screen. Test your typing speed and accuracy while improving your keyboard skills!

## Features

### 🎮 Core Gameplay
- **Moving Words**: Words scroll across the screen from right to left
- **Real-time Typing**: Type words as they appear to score points
- **Word Highlighting**: Active words are highlighted when you start typing them
- **Progressive Difficulty**: Game becomes more challenging as you play
- **Score System**: Track your performance with a built-in scoring system

### ⚙️ Customizable Settings
- **Multiple Resolutions**: 800x600, 1024x768, 1280x720, 1366x768
- **Font Selection**: Choose from 8 different fonts including:
  - Arial (default)
  - PlaywriteIS, PlaywriteFRModerne, PlaywriteNL, PlaywritePL, PlaywriteVN
  - Lora-Italic, Tiny
- **Speed Control**: Adjust word movement speed (Slow/Standard/Fast)
- **Word Frequency**: Control how often new words appear
- **Font Size**: Multiple size options from 20px to 44px

### 🎨 Visual Features
- **Responsive UI**: Interface scales with window size
- **Color-coded Feedback**: 
  - Green for correct typing
  - Yellow for active words
  - Red for missed words counter

### 📚 Word Database
- **Extensive Word List**: 60+ pre-loaded words of varying difficulty
- **Expandable Database**: Easy to add new words via text file
- **Random Selection**: Words are chosen randomly for varied gameplay

## Requirements

### System Requirements
- **OS**: Windows, macOS, or Linux
- **Compiler**: C++20 compatible compiler (GCC 10+, Clang 10+, MSVC 2019+)
- **CMake**: Version 3.30 or higher
- **Graphics**: OpenGL compatible graphics card

### Dependencies
- **SFML 2.6.1**: Automatically downloaded and built via CMake FetchContent
- **Standard C++ Libraries**: filesystem, random, algorithm, fstream

## Installation

### Building from Source

1. **Clone the repository:**
```bash
git clone link
cd typing-game
```

2. **Create build directory:**
```bash
mkdir build
cd build
```

3. **Configure with CMake:**
```bash
cmake ..
```

4. **Build the project:**
```bash
cmake --build .
```

5. **Run the game:**
```bash
./typer_final  # On Linux/macOS
typer_final.exe  # On Windows
```

### CMake Options
The build system automatically:
- Downloads and builds SFML 2.6.1
- Copies all necessary resource files (fonts, backgrounds, word database)
- Configures proper linking and include directories

## How to Play

### Basic Controls
1. **Start Game**: Click "New Game" from the main menu
2. **Type Words**: Simply start typing any word that appears on screen
3. **Complete Words**: Type the entire word correctly to score points
4. **Game Over**: Miss 5 words and the game ends
5. **Return to Menu**: Press ESC during gameplay or after game over

### Scoring System
- **+1 Point**: For each correctly typed word
- **Miss Counter**: Tracks words that scroll off screen
- **Game Over**: After missing 5 words

## Project Structure

```
typing-game/
├── CMakeLists.txt              # Build configuration
├── src/                        # Source code
│   ├── main.cpp               # Application entry point
│   ├── Game.cpp/.h            # Main game logic and state management
│   ├── MovingWord.cpp/.h      # Individual word objects
│   ├── GameSettings.cpp/.h    # Configuration and settings
│   ├── MenuSystem.cpp/.h      # Menu navigation and UI
│   └── WordDatabase.cpp/.h    # Word loading and management
├── fonts/                     # Font files
│   ├── arial.ttf             # Default font
│   ├── PlaywriteIS.ttf       # Alternative fonts
│   ├── Lora-Italic.ttf       # ...
│   └── ...                   # More font options
├── background/                # Background images
│   ├── back.png              # Menu background
│   └── sky.jpg               # Game background
└── resources/                 # Game data
    └── words.txt             # Word database
```

## Configuration Files

### Word Database (resources/words.txt)
Add new words by editing the text file:
```
apple
banana
computer
programming
challenge
```

### Adding New Fonts
1. Place font files in the `fonts/` directory
2. Add font entries to the font selection menu in `MenuSystem.cpp`
3. Rebuild the project

### Custom Backgrounds
Replace image files in the `background/` directory:
- `back.png` - Menu background
- `sky.jpg` - Gameplay background

## Development

### Architecture Overview

#### Game Class
- **Core game loop**: Update, render, event handling
- **State management**: Menu/gameplay/game over states
- **Resource management**: Textures, fonts, sounds
- **Game logic**: Scoring, collision detection, word spawning

#### MovingWord Class
- **Word representation**: Text rendering and positioning
- **Movement mechanics**: Smooth scrolling animation
- **String operations**: Wide string support for text matching

#### MenuSystem Class
- **Navigation**: Multi-level menu system
- **Settings**: Real-time configuration changes
- **Responsive design**: Scales with window resolution
- **Font preview**: Live font switching in menus

#### GameSettings Class
- **Configuration storage**: All game parameters
- **Resource loading**: Fonts, textures, backgrounds
- **Validation**: Ensures settings are within valid ranges

#### WordDatabase Class
- **File parsing**: Loads words from text files
- **Random selection**: Ensures varied gameplay
- **Error handling**: Graceful fallback to generated words

## Technical Details

### Performance Optimizations
- **Efficient rendering**: Only draws visible elements
- **Memory management**: Automatic cleanup of off-screen words
- **Frame rate limiting**: Consistent 60 FPS gameplay
- **Resource caching**: Fonts and textures loaded once

### Cross-Platform Compatibility
- **CMake build system**: Works on Windows, macOS, and Linux
- **SFML library**: Provides consistent behavior across platforms
- **Standard C++**: Uses only portable C++20 features
- **Resource bundling**: All assets copied during build process

### Error Handling
- **Graceful degradation**: Falls back to default resources if custom ones fail
- **User feedback**: Clear error messages for common issues
- **Robust file handling**: Handles missing or corrupted resource files

### Common Issues

**Build Errors:**
- Ensure CMake 3.30+ is installed
- Check that your compiler supports C++20
- Verify internet connection (SFML is downloaded during build)

**Runtime Errors:**
- Make sure resource files are in the correct directories
- Verify font files are not corrupted
