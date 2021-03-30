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
Core::Core() : _dispM({"sdl2"}), _gameM({"nibbler"}) {
    _input = NONE;
    _isRunning = false;
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
    while (this->_isRunning && disp == _dispM.get())
        gameLoop(disp);
    disp->destroyWindow();
}

void Core::gameLoop(IDisplay *disp) {
    IGame *game = _gameM.get();

    while (this->_isRunning && disp == _dispM.get() && game == _gameM.get()) {
        _input = disp->getInput();
        this->execKeys();
    }
}

void Core::execKeys(void) {
    try {
        _handlers[_input]();
    } catch (const std::bad_function_call &_) {}
}

void Core::mapInputs(void) {
    _handlers.emplace(ESCAPE, [this]() { this->_isRunning = false; });
}
}  // namespace arc
