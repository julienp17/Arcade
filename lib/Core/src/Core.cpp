/*
** EPITECH PROJECT, 2021
** arcade [WSL: Ubuntu-20.04]
** File description:
** Core
*/

#include <iostream>
#include "Core.hpp"
#include "IDisplay.hpp"

namespace arc {
Core::Core() : _dispM({"sdl2", "ncurses"}), _gameM({"nibbler"}) {
    _isRunning = false;
    _scene = GAME;
    this->mapInputs();
}

void Core::run(void) {
    _isRunning = true;
    while (this->_isRunning)
        dispLoop();
}

void Core::dispLoop(void) {
    IDisplay *disp = _dispM.get();

    disp->createWindow();
    while (this->_isRunning && disp == _dispM.get()) {
        //menuLoop(disp);
        gameLoop(disp);
    }
    disp->destroyWindow();
}

void Core::menuLoop(IDisplay *disp) {
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
    while (this->_isRunning && disp == _dispM.get() && _scene == MENU)
        this->execKeys(disp->getInput());
}

void Core::gameLoop(IDisplay *disp) {
    IGame *game = _gameM.get();

    while (this->_isRunning && disp == _dispM.get() && _scene == GAME && game == _gameM.get()) {
        this->execKeys(disp->getInput());
        disp->clear();
        disp->drawText(50, 10, game->getName().c_str());
        disp->drawMap(game->getMap());
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
