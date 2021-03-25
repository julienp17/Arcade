/*
** EPITECH PROJECT, 2021
** arcade
** File description:
** Nibbler
*/

#include "Nibbler.hpp"

arc::Nibbler::Nibbler(char **map, std::vector<arc::Parser::item> items) {
    this->_map = map;
    this->_direction = arc::RIGHT;
    this->_tale = {0, 0};
    for (auto item : items)
    {
        if (item.type == std::string("wall"))
            _wallSym = item.sym;
        if (item.type == std::string("snake"))
            _snakeSym = item.sym;
        if (item.type == std::string("bg"))
            _bgSym = item.sym;
    }
    for (size_t y = 0; map[y]; y++) {
        for (size_t x = 0; map[y][x]; x++) {
            if (map[y][x] == this->_snakeSym) {
                this->_head = {x, y};
                return;
            }
        }
    }
}

void arc::Nibbler::execKey(arc::Input key) {
    if (key == this->_direction)
        return;
    this->_direction = key;
}
