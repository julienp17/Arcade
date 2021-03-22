/*
** EPITECH PROJECT, 2021
** arcade [WSL: Ubuntu-20.04]
** File description:
** SDLDisplay
*/

#include <SDL2/SDL.h>
#include "SDLDisplay.hpp"
#include "Error.hpp"

namespace arc {
SDLDisplay::SDLDisplay(void) {
    _win = nullptr;
    _ren = nullptr;
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        throw DisplayError(SDL_GetError());
}

SDLDisplay::~SDLDisplay(void) {
    if (this->_win != nullptr)
        this->destroyWindow();
    if (this->_ren != nullptr)
        SDL_DestroyRenderer(_ren);
    SDL_Quit();
}

void SDLDisplay::createWindow(void) {
    // TODO(julien): make width and height not hardcoded
    if (SDL_CreateWindowAndRenderer(1000, 1000, 0, &_win, &_ren) == -1)
        throw DisplayError(SDL_GetError());
    SDL_SetRenderDrawColor(_ren, 0, 0, 0, 0);
    SDL_RenderClear(_ren);
}

void SDLDisplay::destroyWindow(void) {
    SDL_DestroyWindow(_win);
}

bool SDLDisplay::windowIsOpen(void) const {
    return _event.type != SDL_QUIT;
}

void SDLDisplay::display() const {
    SDL_RenderPresent(_ren);
}

void SDLDisplay::clear() {
    SDL_RenderClear(_ren);
}

Input SDLDisplay::getInput(void) {
    while (SDL_PollEvent(&_event)) {
        // TODO(julien) : implement case SDL_QUIT
        switch (_event.type) {
            case SDL_KEYDOWN:
                switch (_event.key.keysym.scancode) {
                    case SDL_SCANCODE_Z:
                    case SDL_SCANCODE_UP:
                        return UP;

                    case SDL_SCANCODE_Q:
                    case SDL_SCANCODE_LEFT:
                        return LEFT;

                    case SDL_SCANCODE_S:
                    case SDL_SCANCODE_DOWN:
                        return DOWN;

                    case SDL_SCANCODE_D:
                    case SDL_SCANCODE_RIGHT:
                        return RIGHT;

                    default:
                        break;
                }
            default:
                break;
        }
    }
    return NONE;
}
}  // namespace arc
