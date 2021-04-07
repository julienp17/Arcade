/*
** EPITECH PROJECT, 2021
** arcade
** File description:
** Pacman
*/

#ifndef LIB_GAMES_NIBBLER_INC_NIBBLER_HPP_
#define LIB_GAMES_NIBBLER_INC_NIBBLER_HPP_

#include <vector>
#include <string>
#include "IGame.hpp"
#include "Parser.hpp"
#include "arcade.hpp"

namespace arc {
class Pacman : public IGame {
 public:
    Pacman(void);
    Pacman(char **map, std::vector<arc::item> items);
    virtual ~Pacman(void) {}

    void execKey(arc::Input key) override;
    inline char **getMap(void) override {return _map;};
    void tick(void) override;
    inline void reset(void) override {init(_tempMap, _tempItems);};
    inline GAMESTATE getGameState() const {return _state;};
    inline std::string getName(void) const override {return "pacman";};
    inline std::vector<item> getItems(void) const override {return _tempItems;};
 private:
    void init(char **map, std::vector<arc::item> items);
    struct pos {
        int x;
        int y;
    };
    struct ghost {
        pos pos;
        arc::Input direction;
    };
    void movePacman(void);
    void moveGhosts(void);
    pos getVectFromDirection(Input direction);
    void updateSnakePos(void);
    void clearMap(void);

    GAMESTATE _state;
    char **_tempMap;
    char **_map;
    std::vector<item> _tempItems;
    arc::Input _direction;
    char _wallSym;
    char _pacmanSym;
    char _bgSym;
    char _ghostSym;
    pos _pacman;
    std::vector<ghost> _ghosts;
};
}  // namespace arc

#endif  // LIB_GAMES_NIBBLER_INC_NIBBLER_HPP_
