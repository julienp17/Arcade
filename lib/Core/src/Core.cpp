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
Core::Core() : _dispM({"sdl2"}) {
    _input = NONE;
    this->mapInputs();
}

void Core::run(void) {
    IDisplay *disp = nullptr;

    while (this->_isRunning) {
        disp = _dispM.get();
        disp->createWindow();
        while (_input != O && _input != P && _input != ESCAPE) {
            _input = disp->getInput();
            this->execKeys();
        }
        disp->destroyWindow();
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
