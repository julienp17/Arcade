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
    _scene = GAME;
    this->loadLibs();
    _dispM.set(selectedDisplay.get()->get()->getName());
}

void Core::loadLibs(void) {
    const std::string filename = "./conf/core.conf";
    std::ifstream file(filename);
    std::string line;
    auto split = [] (const std::string &s, char delim) {
        std::vector<std::string> result;
        std::stringstream ss(s);
        std::string item;

        while (getline(ss, item, delim))
            result.push_back(item);
        return result;
    };

    if (file.is_open() == false)
        throw CoreError("Cannot open " + filename);
    if (!getline(file, line))
        throw CoreError("Coudln't find display names in " + filename);
    _dispM.loadLibs(split(line, ' '));
    if (!getline(file, line))
        throw CoreError("Coudln't find game names in " + filename);
    _gameM.loadLibs(split(line, ' '));
    file.close();
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
        menuLoop(disp);
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

    // Your name box
    disp->drawBox(10, 20, 80, 10);
    // Displays box
    disp->drawBox(10, 40, 40, 50);
    // Scores box
    disp->drawBox(80, 40, 10, 50);
    // Games Box
    disp->drawBox(50, 40, 30, 50);

    disp->drawText(50, 10, "Arcade");
    disp->drawText(50, 20, "Your name");
    disp->drawText(30, 40, "Displays");
    disp->drawText(65, 40, "Games");
    disp->drawText(85, 40, "Scores");
    disp->display();
    while (menuIsRunning())
        this->execKeys(disp->getInput());
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

    while (gameIsRunning()) {
        input = disp->getInput();
        this->execKeys(input);
        disp->clear();
        if (game->getState() == RUNNING) {
            game->execKey(input);
            game->tick();
            disp->drawMap(game->getMap());
        } else {
            disp->drawText(50, 50, game->getState() == WIN ?
                            "You won !" : "You lost !");
        }
        disp->display();
    }
}

void Core::execKeys(const Input input) {
    try {
        _handlers[input]();
    } catch (const std::bad_function_call &_) {}
}

void Core::mapInputs(void) {
    _handlers.emplace(ESCAPE, [this]() { this->_isRunning = false; });
    _handlers.emplace(O, [this]() { _dispM.prev(); });
    _handlers.emplace(P, [this]() { _dispM.next(); });
    _handlers.emplace(L, [this]() { _gameM.prev(); });
    _handlers.emplace(M, [this]() { _gameM.next(); });
}
}  // namespace arc
