/*
** EPITECH PROJECT, 2021
** arcade
** File description:
** Paman
*/


#include <chrono>
#include <iostream>
#include "Pacman.hpp"
#include "Parser.hpp"

namespace arc {
Pacman::Pacman(void) {
    Parser parser("./conf/pacman.ini");

    this->init(parser.getMap(), parser.getItems());
}

Pacman::Pacman(char **map, std::vector<item> items) {
    this->init(map, items);
}

void Pacman::init(char **map, std::vector<item> items) {
    this->_map = map;
    this->_tempItems = items;
    this->_tempMap = map;
    this->_direction = RIGHT;
    this->_state = RUNNING;
    for (auto item : items) {
        if (item.type == std::string("wall"))
            _wallSym = item.sym;
        if (item.type == std::string("pacman"))
            _pacmanSym = item.sym;
        if (item.type == std::string("background"))
            _bgSym = item.sym;
        if (item.type == std::string("ghost"))
            _ghostSym = item.sym;
    }
    for (int y = 0; map[y]; y++) {
        for (int x = 0; map[y][x]; x++) {
            if (map[y][x] == this->_pacmanSym)
                this->_pacman = {x, y};
            if (map[y][x] ==  this->_ghostSym)
                this->_ghosts.push_back({{x, y}, RIGHT});
        }
    }
}

void Pacman::execKey(Input key) {
    if (key != DOWN && key != UP && key != LEFT && key != RIGHT)
        return;
    if (key == this->_direction)
        return;
    this->_direction = key;
}

void Pacman::tick(void) {
    static auto lastCall = std::chrono::high_resolution_clock::now();
    auto  now = std::chrono::high_resolution_clock::now();
    auto duration =
        std::chrono::duration_cast<std::chrono::milliseconds>(now - lastCall);

    if (duration <= std::chrono::milliseconds{500})
        return;
    while (duration > std::chrono::milliseconds{500}) {
        if (_state == LOOSE)
            return;
        this->movePacman();
        duration -= std::chrono::milliseconds{500};
    }
    lastCall = std::chrono::high_resolution_clock::now();
}

void Pacman::movePacman(void) {
    Pacman::pos vect = this->getVectFromDirection(this->_direction);

    if (_map[_pacman.y + vect.y][_pacman.x + vect.x] == _ghostSym) {
        _state = LOOSE;
        return;
    }
    if (_map[_pacman.y + vect.y][_pacman.x + vect.x] != _wallSym) {
        _map[_pacman.y][_pacman.x] = _bgSym;
        _map[_pacman.y + vect.y][_pacman.x + vect.x] = _pacmanSym;
    }
}
}  // namespace arc