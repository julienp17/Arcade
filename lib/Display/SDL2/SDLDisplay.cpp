/*
** EPITECH PROJECT, 2021
** arcade [WSL: Ubuntu-20.04]
** File description:
** SDLDisplay
*/

#include <SDL2/SDL.h>
#include <iostream>
#include "SDLDisplay.hpp"
#include "Error.hpp"

namespace arc {
SDLDisplay::SDLDisplay(void) {
    _win = nullptr;
    _ren = nullptr;
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0)
        throw DisplayError(SDL_GetError());
}

SDLDisplay::~SDLDisplay(void) {
    SDL_Quit();
}

void SDLDisplay::createWindow(void) {
    // TODO(julien): make width and height not hardcoded
    if (SDL_CreateWindowAndRenderer(1000, 1000, 0, &_win, &_ren) == -1)
        throw DisplayError(std::string("SDL2: ") + SDL_GetError());
    SDL_SetRenderDrawColor(_ren, 0, 0, 0, 0);
    SDL_RenderClear(_ren);
}

void SDLDisplay::destroyWindow(void) {
    SDL_DestroyWindow(_win);
    _win = nullptr;
    SDL_DestroyRenderer(_ren);
    _ren = nullptr;
}

void SDLDisplay::display() const {
    SDL_RenderPresent(_ren);
}

void SDLDisplay::clear() {
    SDL_RenderClear(_ren);
}

Input SDLDisplay::getInput(void) const {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                return ESCAPE;
            case SDL_KEYDOWN:
                return this->getInputKey(event);
            default:
                break;
        }
    }
    return NONE;
}

Input SDLDisplay::getInputKey(const SDL_Event &event) const {
    switch (event.key.keysym.scancode) {
        case SDL_SCANCODE_ESCAPE:
            return ESCAPE;

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
    return NONE;
}

extern "C" IDisplay *create(void) {
    return new SDLDisplay;
}

extern "C" void destroy(IDisplay *display) {
    delete display;
}
}  // namespace arc
