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

Nibbler::Nibbler(char **map, std::vector<item> items) {
    this->init(map, items);
}

void Nibbler::init(char **map, std::vector<item> items) {
    this->_map = map;
    this->_tempItems = items;
    this->_tempMap = map;
    this->_tailDirection = RIGHT;
    this->_direction = RIGHT;
    this->_state = RUNNING;
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
                this->_snake.push_back({x, y});
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
}


void Nibbler::tick(void) {
    static auto lastCall = std::chrono::high_resolution_clock::now();
    auto  now = std::chrono::high_resolution_clock::now();
    auto duration =
        std::chrono::duration_cast<std::chrono::milliseconds>(now - lastCall);

    if (duration <= std::chrono::milliseconds{500})
        return;
    while (duration > std::chrono::milliseconds{500}) {
        if (_state == LOOSE)
            return;
        this->moveSnake();
        duration -= std::chrono::milliseconds{500};
    }
    lastCall = std::chrono::high_resolution_clock::now();
}

void Nibbler::moveSnake(void) {
    Nibbler::pos vect = this->getVectFromDirection(this->_direction);
    pos head = _snake[0];

    if (_map[head.y + vect.y][head.x + vect.x] == _wallSym ||
        _map[head.y + vect.y][head.x + vect.x] == _snakeSym) {
        _state = LOOSE;
        return;
    }
    if (_map[head.y + vect.y][head.x + vect.x] == _eggSym)
        _snake.insert(_snake.begin(), {head.x + vect.x, head.y + vect.y});
    else
        this->updateSnakePos();
    this->clearMap();
    for (size_t i = 0; i != _snake.size(); i++)
        _map[_snake[i].y][_snake[i].x] = _snakeSym;
}

void Nibbler::updateSnakePos(void) {
    Nibbler::pos vect = this->getVectFromDirection(this->_direction);
    pos prevPart {0, 0};
    pos tmpPart {0, 0};

    prevPart = {_snake[0].x + vect.x, _snake[0].y + vect.y};
    for (size_t i = 0; i != _snake.size(); i++) {
        tmpPart = {_snake[i].x, _snake[i].y};
        _snake[i] = prevPart;
        prevPart = tmpPart;
    }
}

void Nibbler::clearMap(void) {
    for (size_t y = 0; _map[y]; y++)
        for (size_t x = 0; _map[y][x]; x++)
            if (_map[y][x] == _snakeSym)
                _map[y][x] = _bgSym;
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

extern "C" LibType getLibType(void) {
    return GAME;
}

extern "C" IGame *create(void) {
    return new Nibbler;
}

extern "C" void destroy(IGame *game) {
    delete game;
}
}  // namespace arc
