cmake_minimum_required(VERSION 3.30)
project(typer_final)

set(CMAKE_CXX_STANDARD 20)
set(BUILD_SHARED_LIBS FALSE)

include(FetchContent)

FetchContent_Declare(
        SFML
        GIT_REPOSITORY  https://github.com/SFML/SFML
        GIT_TAG         2.6.1
)

FetchContent_MakeAvailable(SFML)

set(SOURCES
        src/main.cpp
        src/Game.cpp
        src/MovingWord.cpp
        src/GameSettings.cpp
        src/MenuSystem.cpp
        src/WordDatabase.cpp
)

set(HEADERS
        src/Game.h
        src/MovingWord.h
        src/GameSettings.h
        src/MenuSystem.h
        src/WordDatabase.h
)

add_executable(typer_final ${SOURCES} ${HEADERS})

target_link_libraries(typer_final sfml-graphics sfml-window sfml-system)

target_include_directories(typer_final PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(RESOURCE_DIRS
        fonts
        background
        resources
)

foreach(DIR ${RESOURCE_DIRS})
    file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/${DIR})
endforeach()

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/fonts DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/background DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/resources DESTINATION ${CMAKE_BINARY_DIR})