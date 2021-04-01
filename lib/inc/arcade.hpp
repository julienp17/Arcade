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
typedef char ** map_t;

enum Input {
    NONE,
    ESCAPE,
    LEFT,
    RIGHT,
    UP,
    DOWN,
    A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z
};
enum GAMESTATE {
    WIN,
    LOOSE,
    RUNNING
};
}  // namespace arc

#endif  // LIB_INC_ARCADE_HPP_
