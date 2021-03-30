/*
** EPITECH PROJECT, 2021
** arcade [WSL: Ubuntu-20.04]
** File description:
** Core
*/

#ifndef LIB_CORE_INC_CORE_HPP_
#define LIB_CORE_INC_CORE_HPP_

#include <unordered_map>
#include <functional>
#include "arcade.hpp"
#include "DLManager.hpp"
#include "IDisplay.hpp"
#include "IGame.hpp"

namespace arc {
/** @class Core
 * @brief Bridge between a game library and a display library
 */
class Core {
 public:
    /**
     * @brief Construct a new Core object
     */
    Core(void);

    /**
     * @brief Destroy the Core object
     */
    ~Core(void) {}

    /**
     * @brief Launches the arcade !
     */
    void run(void);

    /**
     * @brief Handles the inputs related to arcade
     */
    void execKeys(void);

    /**
     * @brief Retrieve an input from the current display library
     * 
     * @return An enum Input
     */
    Input getInput(void);

    // void saveHiScore();

 private:
    void dispLoop(void);
    void gameLoop(IDisplay *disp);

    /**
     * @brief Map the inputs to their corresponding action
     */
    void mapInputs(void);
    typedef std::function<void(void)> handler;

    bool _isRunning;
    Input _input;

    //* Display Manager
    DLManager<IDisplay> _dispM;

    //* Game Manager
    DLManager<IGame> _gameM;

    //* Events handlers
    std::unordered_map<Input, handler> _handlers;
};
}  // namespace arc


#endif  // LIB_CORE_INC_CORE_HPP_
