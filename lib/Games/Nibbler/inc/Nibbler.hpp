/*
** EPITECH PROJECT, 2021
** arcade
** File description:
** Nibbler
*/

#ifndef LIB_GAMES_NIBBLER_INC_NIBBLER_HPP_
#define LIB_GAMES_NIBBLER_INC_NIBBLER_HPP_

#include <vector>
#include "IGame.hpp"
#include "Parser.hpp"
#include "arcade.hpp"

namespace arc {
class Nibbler : public IGame {
 public:
    Nibbler(void);
    Nibbler(char **map, std::vector<arc::Parser::item> items);
    virtual ~Nibbler(void) {}

    void execKey(arc::Input key) override;
    inline char **getMap(void) override {return _map;};
    void tick(void) override;
    inline void reset(void) override {init(_tempMap, _tempItems);};
    inline GAMESTATE getGameState() const {return _state;};

 private:
    void init(char **map, std::vector<arc::Parser::item> items);
    struct pos {
        int x;
        int y;
    };
    bool canChangeDirection(arc::Input key);
    void moveSnake(void);
    pos getVectFromDirection(Input direction);
    pos findNewTail(void);

    GAMESTATE _state;
    char **_tempMap;
    std::vector<Parser::item> _tempItems;
    char **_map;
    arc::Input _direction;
    char _wallSym;
    char _snakeSym;
    char _bgSym;
    char _eggSym;
    pos _head;
    pos _tail;
};
}  // namespace arc

#endif  // LIB_GAMES_NIBBLER_INC_NIBBLER_HPP_
