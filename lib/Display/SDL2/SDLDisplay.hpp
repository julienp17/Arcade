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
#include "Error.hpp"
#include "SDL_ttf.h"

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
     * @brief Destroys the SDL Window and renderer
     */
    void destroyWindow(void) override;

    /**
     * @brief Displays the SDL window
     */
    void display(void) const override;

    /**
     * @brief Draw the game map
     */
    void drawMap(map_t map) const override;

    /**
     * @brief Draws text to the SDL window
     *
     * @param x Percentage of the width
     * @param y Percentage of the height
     * @param text The text to be drawn
     */
    void drawText(int x, int y, const char *text) override;

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
    Input getInput(void) const override;

    /**
     * @brief Get the name of the library
     *
     * @return "sdl2"
     */
    std::string getName(void) const override {
        return "sdl2";
    }

 private:
    /**
     * @brief Poll an input
     *
     * @return Input An enum of the one of the input if a recognized key is
     * pressed, NONE otherwise
     */
    Input getInputKey(const SDL_Event &event) const;

    const SDL_Color _WHITE = {255, 255, 255, 0};
    const SDL_Color _BLACK = {0, 0, 0, 0};

    SDL_Window *_win;
    SDL_Renderer *_ren;
    TTF_Font *_font;
};

class SDLError : public Error {
 public:
    SDLError(void) : Error(std::string("SDL2: ") + SDL_GetError()) {}
    explicit SDLError(std::string const &message)
        : Error(std::string("SDL2: ") + message) {}
};

class TTFError : public SDLError {
 public:
    TTFError(void) : SDLError(std::string("TTF: ") + TTF_GetError()) {}
    explicit TTFError(std::string const &message)
        : SDLError(std::string("TTF: ") + message) {}
};
}  // namespace arc

#endif  // LIB_SDL2_INC_SDLDISPLAY_HPP_
