/*
** EPITECH PROJECT, 2021
** arcade [WSL: Ubuntu-20.04]
** File description:
** CoreMenu
*/

#include "Core.hpp"

namespace arc {
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

    for (size_t i = 0 ; i < dispLibNames.size() ; i++) {
        if (disp->getName() == dispLibNames[i])
            disp->drawBox(10, 46 + i * 10, 30, 10);
        disp->drawText(25, 50 + i * 10, dispLibNames[i].c_str());
    }
    for (size_t i = 0 ; i < gameLibNames.size() ; i++) {
        disp->drawText(55, 50 + i * 10, gameLibNames[i].c_str());
        disp->drawText(80, 50 + i * 10,
            std::to_string(this->getHiScore(gameLibNames[i])).c_str());
    }
}

void Core::mapInputsMenu(void) {
    _handlers.clear();
    _handlers.emplace(ESCAPE, [this]() { this->_isRunning = false; });
    _handlers.emplace(UP, [this]() { _dispM.prev(); });
    _handlers.emplace(DOWN, [this]() { _dispM.next(); });
}
}  // namespace arc
