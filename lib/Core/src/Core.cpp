/*
** EPITECH PROJECT, 2021
** arcade [WSL: Ubuntu-20.04]
** File description:
** Core
*/

#include <iostream>
#include <sstream>
#include <thread>
#include <chrono>
#include <fstream>
#include "Core.hpp"
#include "IDisplay.hpp"

namespace arc {
Core::Core(const std::string &filename) {
    std::unique_ptr<DispLoader> selectedDisplay =
        std::unique_ptr<DispLoader>(new DispLoader(filename));

    _isRunning = false;
    _scene = MENU;
    _dispM.loadLibs();
    _gameM.loadLibs();
    for (const std::string &libName : _dispM.getLibNames()) {
        std::cout
            << "[DISPLAY] Successfully loaded '" << libName << "' library"
            << std::endl;
    }
    for (const std::string &libName : _gameM.getLibNames()) {
        std::cout
            << "[GAME] Successfully loaded '" << libName << "' library"
            << std::endl;
    }
    _dispM.set(selectedDisplay.get()->get()->getName());
    std::cout
        << "[DISPLAY] Setting '" << _dispM.get()->getName()
        << "' as starting display library" << std::endl;
}

void Core::run(void) {
    _isRunning = true;
    this->mapInputs();
    while (this->_isRunning)
        dispLoop();
}

void Core::dispLoop(void) {
    IDisplay *disp = _dispM.get();
    auto dispIsRunning = [this, disp] (void) {
        return (this->_isRunning
            && disp == _dispM.get());
    };

    disp->createWindow();
    while (dispIsRunning()) {
        if (_scene == MENU)
            menuLoop(disp);
        else if (_scene == GAME)
            gameLoop(disp);
    }
    disp->destroyWindow();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

void Core::menuLoop(IDisplay *disp) {
    auto menuIsRunning = [this, disp] (void) {
        return (this->_isRunning
            && disp == _dispM.get()
            && _scene == MENU);
    };

    while (menuIsRunning()) {
        this->execKeys(disp->getInput());
        disp->clear();
        this->drawMenu(disp);
        disp->display();
    }
}

void Core::drawMenu(IDisplay *disp) const {
    std::vector<std::string> dispLibNames = _dispM.getLibNames();
    std::vector<std::string> gameLibNames = _gameM.getLibNames();

    // Your name box
    disp->drawBox(10, 25, 80, 10);
    // Displays box
    disp->drawBox(10, 45, 30, 50);
    // Scores box
    disp->drawBox(70, 45, 20, 50);
    // Games Box
    disp->drawBox(40, 45, 30, 50);
    disp->drawText(50, 10, "Arcade");
    disp->drawText(50, 20, "Your name");
    disp->drawText(25, 40, "Displays");
    disp->drawText(55, 40, "Games");
    disp->drawText(80, 40, "Scores");

    for (size_t i = 0 ; i < dispLibNames.size() ; i++)
        disp->drawText(25, 50 + i * 10, dispLibNames[i].c_str());
    for (size_t i = 0 ; i < gameLibNames.size() ; i++) {
        disp->drawText(55, 50 + i * 10, gameLibNames[i].c_str());
        disp->drawText(80, 50 + i * 10,
            std::to_string(this->getHiScore(gameLibNames[i])).c_str());
    }
}

void Core::gameLoop(IDisplay *disp) {
    IGame *game = _gameM.get();
    Input input = NONE;
    auto gameIsRunning = [this, disp, game](void) {
        return (this->_isRunning
            && disp == _dispM.get()
            && _scene == GAME
            && game == _gameM.get());
    };

    disp->loadSprites(game->getItems());
    while (gameIsRunning()) {
        input = disp->getInput();
        this->execKeys(input);
        disp->clear();
        if (game->getState() == RUNNING) {
            game->execKey(input);
            game->tick();
            disp->drawMap(game->getMap());
        } else {
            disp->drawText(50, 30, game->getName().c_str());
            disp->drawText(50, 45, game->getState() == WIN ?
                            "You won !" : "You lost !");
            disp->drawText(50, 60, "Press 'R' to reload the game");
            disp->drawText(50, 70, "Press 'T' to return to the menu");
        }
        disp->display();
    }
    this->saveHiScore(game->getName(), game->getScore());
    disp->destroySprites();
}

void Core::execKeys(const Input input) {
    try {
        _handlers[input]();
    } catch (const std::bad_function_call &_) {}
}

size_t Core::getHiScore(const std::string &gameName) const {
    std::string filename = std::string(SCORES_DIR) + gameName + ".score";
    std::ifstream file(filename);
    std::string line;

    if (!file.is_open() || !getline(file, line)) {
        this->saveHiScore(gameName, 0);
        return 0;
    }
    file.close();
    return atoi(line.c_str());
}

void Core::saveHiScore(const std::string &gameName, const size_t score) const {
    std::string filename = std::string(SCORES_DIR) + gameName + ".score";
    std::ofstream file(filename);

    if (!file.is_open())
        throw CoreError("Cannot write to '" + filename + "'");
    file << score;
    file.close();
}

void Core::mapInputs(void) {
    _handlers.emplace(ESCAPE, [this]() { this->_isRunning = false; });
    _handlers.emplace(O, [this]() { _dispM.prev(); });
    _handlers.emplace(P, [this]() { _dispM.next(); });
    _handlers.emplace(L, [this]() { _gameM.prev(); });
    _handlers.emplace(M, [this]() { _gameM.next(); });
    _handlers.emplace(R, [this]() { _gameM.get()->reset();});
    _handlers.emplace(T, [this]() { _scene = MENU; });
}
}  // namespace arc
