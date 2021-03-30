/*
** EPITECH PROJECT, 2021
** arcade
** File description:
** Nibbler
*/

#include <chrono>
#include <iostream>
#include "Nibbler.hpp"
#include "Parser.hpp"

namespace arc {
Nibbler::Nibbler(void) {
    Parser parser("./conf/nibbler.ini");

    this->init(parser.getMap(), parser.getItems());
}

Nibbler::Nibbler(char **map, std::vector<Parser::item> items) {
    this->init(map, items);
}

void Nibbler::init(char **map, std::vector<Parser::item> items) {
    this->_map = map;
    this->_direction = RIGHT;
    this->_state = IGame::RUNNING;
    for (auto item : items) {
        if (item.type == std::string("wall"))
            _wallSym = item.sym;
        if (item.type == std::string("snake"))
            _snakeSym = item.sym;
        if (item.type == std::string("background"))
            _bgSym = item.sym;
        if (item.type == std::string("egg"))
            _eggSym = item.sym;
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

void Nibbler::execKey(Input key) {
    if (key != DOWN && key != UP && key != LEFT && key != RIGHT)
        return;
    if (key == this->_direction)
        return;
    this->_direction = key;
    this->moveSnake();
}


char **Nibbler::getMap(void) {
    static auto lastCall = std::chrono::high_resolution_clock::now();
    auto  now = std::chrono::high_resolution_clock::now();
    auto duration =
        std::chrono::duration_cast<std::chrono::milliseconds>(now - lastCall);

    if (duration <= std::chrono::milliseconds{500})
        return _map;
    while (duration > std::chrono::milliseconds{500}) {
        if (_state == IGame::LOOSE)
            return _map;
        this->moveSnake();
        duration -= std::chrono::milliseconds{500};
    }
    lastCall = std::chrono::high_resolution_clock::now();
    return _map;
}

void Nibbler::moveSnake(void) {
    Nibbler::pos vect = this->getVectFromDirection(this->_direction);

    if (_map[_head.y + vect.y][_head.x + vect.x] == _wallSym ||
        _map[_head.y + vect.y][_head.x + vect.x] == _snakeSym) {
        _state = IGame::LOOSE;
        return;
    }

    if (_map[_head.y + vect.y][_head.x + vect.x] != _eggSym) {
        _map[_tail.y][_tail.x] = _bgSym;
        _tail = findNewTail();
    }
    _map[_head.y + vect.y][_head.x + vect.x] = _snakeSym;
    _head = {_head.x + vect.x, _head.y + vect.y};
}

Nibbler::pos Nibbler::getVectFromDirection(Input direction) {
    if (direction == LEFT)
        return {-1, 0};
    if (direction == RIGHT)
        return {1, 0};
    if (direction == UP)
        return {0, -1};
    return {0, 1};
}

Nibbler::pos Nibbler::findNewTail(void) {
    if (_map[_tail.y + 1][_tail.x] == _snakeSym)
        return {_tail.x, _tail.y + 1};
    if (_map[_tail.y - 1][_tail.x] == _snakeSym)
        return {_tail.x, _tail.y - 1};
    if (_map[_tail.y][_tail.x + 1] == _snakeSym)
        return {_tail.x + 1, _tail.y};
    if (_map[_tail.y][_tail.x - 1] == _snakeSym)
        return {_tail.x - 1, _tail.y};
    return {0, 0};
}

extern "C" IGame *create(void) {
    return new Nibbler;
}

extern "C" void destroy(IGame *game) {
    delete game;
}
}  // namespace arc
