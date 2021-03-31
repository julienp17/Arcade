/*
** EPITECH PROJECT, 2021
** arcade [WSL: Ubuntu-20.04]
** File description:
** arcade
*/

#ifndef LIB_INC_ARCADE_HPP_
#define LIB_INC_ARCADE_HPP_

#define MY_EXIT_FAILURE     84
#define USAGE \
"Usage: arcade GRAPHIC_LIBRARY"

namespace arc {
enum Input {
    NONE,
    LEFT,
    RIGHT,
    UP,
    DOWN
};
enum GAMESTATE {
    WIN,
    LOOSE,
    RUNNING
};
}  // namespace arc

#endif  // LIB_INC_ARCADE_HPP_
