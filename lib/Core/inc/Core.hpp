/*
** EPITECH PROJECT, 2021
** arcade [WSL: Ubuntu-20.04]
** File description:
** Core
*/

#ifndef LIB_CORE_INC_CORE_HPP_
#define LIB_CORE_INC_CORE_HPP_

#include "arcade.hpp"
#include "DLManager.hpp"
#include "IDisplay.hpp"

namespace arc {
class Core {
 public:
    /**
     * @brief Construct a new Core object
     */
    Core(void) : _dispM({"sdl2"}) {}

    /**
     * @brief Destroy the Core object
     */
    ~Core(void) {}

    /**
     * @brief Retrieve an input from the current display library
     * 
     * @return An enum Input
     */
    Input getInput(void);

    // void saveHiScore();

 private:
    //* Display Manager
    DLManager<IDisplay> _dispM;
};
}  // namespace arc


#endif  // LIB_CORE_INC_CORE_HPP_
