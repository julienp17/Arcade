/*
** EPITECH PROJECT, 2021
** arcade
** File description:
** Nibbler
*/

#include <chrono>
#include "Nibbler.hpp"

arc::Nibbler::Nibbler(char **map, std::vector<arc::Parser::item> items) {
    this->_map = map;
    this->_direction = arc::RIGHT;
    this->_state = arc::IGame::RUNNING;
    for (auto item : items) {
        if (item.type == std::string("wall"))
            _wallSym = item.sym;
        if (item.type == std::string("snake"))
            _snakeSym = item.sym;
        if (item.type == std::string("background"))
            _bgSym = item.sym;
    }
    for (int y = 0; map[y]; y++) {
        for (int x = 0; map[y][x]; x++) {
            if (map[y][x] == this->_snakeSym) {
                this->_head = {x, y};
                this->_tail = this->_head;
                return;
            }
        }
    }
}

void arc::Nibbler::execKey(arc::Input key) {
    if (key == this->_direction)
        return;
    this->_direction = key;
    this->moveSnake();
}


char **arc::Nibbler::getMap(void) {
    static auto lastCall = std::chrono::high_resolution_clock::now();
    auto  now = std::chrono::high_resolution_clock::now();
    auto duration =
        std::chrono::duration_cast<std::chrono::milliseconds>(now - lastCall);

    if (duration <= std::chrono::milliseconds{1000})
        return _map;
    while (duration > std::chrono::milliseconds{1000}) {
        this->moveSnake();
        duration -= std::chrono::milliseconds{1000};
    }
    lastCall = std::chrono::high_resolution_clock::now();
    return _map;
}

void arc::Nibbler::moveSnake(void) {
    arc::Nibbler::pos vect = this->getVectFromDirection(this->_direction);

    if (_map[_head.y + vect.y][_head.x + vect.x] == _wallSym)
        _state = arc::IGame::LOOSE;
    // TODO(tristan): ajouter le cas ou le snake mange un oeuf
    _map[_head.y + vect.y][_head.x + vect.x] = _snakeSym;
    _map[_tail.y][_tail.x] = _bgSym;
    _tail = findNewTale();
}

arc::Nibbler::pos arc::Nibbler::getVectFromDirection(Input direction) {
    if (direction == arc::LEFT)
        return {-1, 0};
    if (direction == arc::RIGHT)
        return {1, 0};
    if (direction == arc::UP)
        return {0, -1};
    return {0, 1};
}

arc::Nibbler::pos arc::Nibbler::findNewTale(void) {
    if (_map[_tail.y + 1][_tail.x] == _snakeSym)
        return {_tail.y + 1, _tail.x};
    if (_map[_tail.y - 1][_tail.x] == _snakeSym)
        return {_tail.y - 1, _tail.x};
    if (_map[_tail.y][_tail.x + 1] == _snakeSym)
        return {_tail.y, _tail.x + 1};
    if (_map[_tail.y][_tail.x - 1] == _snakeSym)
        return {_tail.y, _tail.x - 1};
    return {0, 0};
}
