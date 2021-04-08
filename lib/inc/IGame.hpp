/*
** EPITECH PROJECT, 2021
** arcade
** File description:
** IGames
*/

#ifndef INC_IGAME_HPP_
#define INC_IGAME_HPP_

#include <string>
#include <vector>
#include "arcade.hpp"

namespace arc {
class IGame {
 public:
    virtual ~IGame(void) {}

    virtual void execKey(arc::Input key) = 0;
    virtual void tick(void) = 0;
    virtual void reset(void) = 0;
    virtual std::vector<item> getItems(void) const = 0;
    virtual char **getMap(void) = 0;
    virtual size_t getScore(void) = 0;
    virtual std::string getName(void) const = 0;
    virtual GAMESTATE getState(void) const = 0;
};
} // namespace arc

#endif /* !IGAME_HPP_ */