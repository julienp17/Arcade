/*
** EPITECH PROJECT, 2021
** arcade [WSL: Ubuntu-20.04]
** File description:
** Core
*/

#ifndef INC_CORE_CORE_HPP_
#define INC_CORE_CORE_HPP_

#include "arcade.hpp"

namespace arc {
class Core {
 public:
    Core();
    ~Core();

    void loadGame();
    void prevGame();
    void nextGame();
    void loadDisplay();
    void prevDisplay();
    void nextDisplay();
    void saveHiScore();
    Input getInput();
};
}  // namespace arc


#endif  // INC_CORE_CORE_HPP_
