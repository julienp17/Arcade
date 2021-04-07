/*
** EPITECH PROJECT, 2021
** arcade [WSL: Ubuntu-20.04]
** File description:
** Core
*/

#ifndef LIB_CORE_INC_CORE_HPP_
#define LIB_CORE_INC_CORE_HPP_

#include <unordered_map>
#include <string>
#include <functional>
#include "arcade.hpp"
#include "DLManager.hpp"
#include "IDisplay.hpp"
#include "IGame.hpp"
#include "Error.hpp"

namespace arc {
/** @class CoreError
 * @brief Errors related to arcade Core
 */
class CoreError : public Error {
 public:
    explicit CoreError(std::string const &message)
        : Error(std::string("core: ") + message) {}
};

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
    virtual ~Core(void) {}

    /**
     * @brief Launches the arcade !
     */
    void run(void);

    // void saveHiScore();

 private:
    typedef std::function<void(void)> handler;

    enum Scene {
        MENU,
        GAME
    };

    /**
     * @brief Handles the inputs related to arcade
     */
    void execKeys(const Input input);

    /**
     * @brief Loads the display and game libraries
     *
     * Called when a Core object is created.
     * Calls the loadLibs method of the display and game manager.
     */
    void loadLibs(void);

    void dispLoop(void);
    void menuLoop(IDisplay *disp);
    void gameLoop(IDisplay *disp);

    /**
     * @brief Map the inputs to their corresponding action
     */
    void mapInputs(void);

    bool _isRunning;

    //* Display Manager
    DLManager<IDisplay> _dispM;

    //* Game Manager
    DLManager<IGame> _gameM;

    //* Current scene
    Scene _scene;

    //* Events handlers
    std::unordered_map<Input, handler> _handlers;
};
}  // namespace arc


#endif  // LIB_CORE_INC_CORE_HPP_
