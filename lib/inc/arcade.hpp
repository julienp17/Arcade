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

#define KEYS_USAGE \
"Keys:\n" \
"   'ESCAPE' - Exit the arcade\n" \
"        'O' - Previous graphics library\n" \
"        'P' - Next graphics library\n" \
"        'L' - Previous game\n" \
"        'M' - Next game\n" \
"        'R' - Restart the game\n" \
"        'T' - Go back to the menu" \

#include <string>
#include <vector>

namespace arc {
const char LIBDIR[] = "./lib/";
const char SCORES_DIR[] = "./.scores/";

enum LibType {
    DISPLAY,
    GAME
};

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

typedef struct item {
    std::string type;
    char sym;
    std::string path;
} item;

typedef std::vector<item> itemVec;
typedef char ** map_t;
}  // namespace arc

#endif  // LIB_INC_ARCADE_HPP_
