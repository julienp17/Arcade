/*
** EPITECH PROJECT, 2021
** arcade [WSL: Ubuntu-20.04]
** File description:
** SDLDisplay
*/

#ifndef LIB_SDL2_INC_SDLDISPLAY_HPP_
#define LIB_SDL2_INC_SDLDISPLAY_HPP_

#include <SDL2/SDL.h>
#include <string>
#include "IDisplay.hpp"

namespace arc {
/** @class SDLDisplay
 * @brief SDL2 Display library
 */
class SDLDisplay : public IDisplay {
 public:
    /**
     * @brief Construct a new SDLDisplay object
     *
     * Initialize SDL with everything
     */
    SDLDisplay(void);

    /**
     * @brief Destroy the SDLDisplay object
     *
     * Calls SDL_Quit()
     */
    virtual ~SDLDisplay(void);

    /**
     * @brief Create an SDL Window and renderer object
     */
    void createWindow(void) override;

    /**
     * @brief Checks whether the window is open
     *
     * @return true The window is open
     * @return false The window is not open
     */
    bool windowIsOpen(void) const override;

    /**
     * @brief Displays the window
     */
    void display(void) const override;

    /**
     * @brief Clears the content of the window
     */
    void clear(void) override;

    /**
     * @brief Poll an input
     *
     * @return Input An enum of the one of the input if a recognized key is
     * pressed, NONE otherwise
     */
    Input getInput(void) override;

    /**
     * @brief Get the name of the library
     * 
     * @return "sdl2"
     */
    std::string getName(void) override {
        return "sdl2";
    }

 private:
    /**
     * @brief Poll an input
     *
     * @return Input An enum of the one of the input if a recognized key is
     * pressed, NONE otherwise
     */
    Input getInputKey(void);

    SDL_Window *_win;
    SDL_Renderer *_ren;
    SDL_Event _event;
};
}  // namespace arc

#endif  // LIB_SDL2_INC_SDLDISPLAY_HPP_
