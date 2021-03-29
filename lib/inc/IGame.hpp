/*
** EPITECH PROJECT, 2021
** arcade
** File description:
** IGames
*/

#ifndef INC_IGAME_HPP_
#define INC_IGAME_HPP_

#include <string>
#include "arcade.hpp"

namespace arc {
class IGame {
 public:
    virtual ~IGame(void) {}

    enum GAMESTATE {
        WIN,
        LOOSE,
        RUNNING
    };

    virtual std::string getName(void) const = 0;
    virtual void execKey(arc::Input key) = 0;
    virtual char **getMap(void) = 0;
};
} // namespace arc

#endif /* !IGAME_HPP_ */
