/*
** EPITECH PROJECT, 2021
** arcade
** File description:
** Nibbler
*/

#ifndef NIBBLER_HPP_
#define NIBBLER_HPP_

#include "IGame.hpp"
#include "Parser.hpp"
#include "arcade.hpp"

namespace arc {
class Nibbler : public IGame {
 public:
    Nibbler(char **map, std::vector<arc::Parser::item> items);
    ~Nibbler(void) {}

    void execKey(arc::Input key) override;
    inline char **getMap(void) override { return _map; };

 private:
    struct pos {
        size_t x;
        size_t y;
    };
    bool canChangeDirection(arc::Input key);
    void moveSnake(void);
    pos getVectFromDirection(Input direction);
    pos findNewTale(void);

    GAMESTATE _state;
    char **_map;
    arc::Input _direction;
    char _wallSym;
    char _snakeSym;
    char _bgSym;
    pos _head;
    pos _tail;
};
} // namespace arc

#endif /* !NIBBLER_HPP_ */