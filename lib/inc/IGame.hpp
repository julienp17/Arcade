/*
** EPITECH PROJECT, 2021
** arcade
** File description:
** IGames
*/

#ifndef INC_IGAME_HPP_
#define INC_IGAME_HPP_

#include "arcade.hpp"

namespace arc {
class IGame {
 public:
    virtual ~IGame(void) {}

    virtual void execKey(arc::Input key) = 0;
    virtual char **getMap(void) = 0;
    virtual void tick(void) = 0;
    // TODO(tristan): virtual void reset(void) = 0;
};
} // namespace arc

#endif /* !IGAME_HPP_ */
