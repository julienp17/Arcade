/*
** EPITECH PROJECT, 2021
** arcade [WSL: Ubuntu-20.04]
** File description:
** NcursesDisplay
*/

#include <string.h>
#include <iostream>
#include "NcursesDisplay.hpp"
#include "Error.hpp"

namespace arc {
void NcursesDisplay::createWindow(void) {
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    timeout(100);
    curs_set(0);
    nodelay(stdscr, true);
    clear();
}

void NcursesDisplay::destroyWindow(void) {
    endwin();
}

void NcursesDisplay::display(void) const {
    refresh();
}

void NcursesDisplay::drawMap(map_t map) const {
    for (size_t i = 0 ; map[i] ; i++) {
        addstr(map[i]);
        addch('\n');
    }
}

void NcursesDisplay::drawText(int x, int y, const char *text) {
    if (x < 0 || x > 100 || y < 0 || y > 100)
        throw DisplayError("x or y percentage not in range [0, 100]");
    x = x * getmaxx(stdscr) / 100;
    y = y * getmaxy(stdscr) / 100;
    mvaddstr(y, x - (strlen(text) / 2), text);
}

void NcursesDisplay::drawBox(int x, int y, int w, int h) {
    x = x * getmaxx(stdscr) / 100;
    y = y * getmaxy(stdscr) / 100;
    w = w * getmaxx(stdscr) / 100;
    h = h * getmaxy(stdscr) / 100;
    mvhline(y, x, 0, w);
    mvhline(y + h, x, 0, w);
    mvvline(y, x, 0, h);
    mvvline(y, x + w, 0, h);
    mvaddch(y, x, ACS_ULCORNER);
    mvaddch(y + h, x, ACS_LLCORNER);
    mvaddch(y, x + w, ACS_URCORNER);
    mvaddch(y + h, x + w, ACS_LRCORNER);
}

void NcursesDisplay::clear(void) {
    erase();
}

Input NcursesDisplay::getInput(void) const {
    int c = getch();

    switch (c) {
    case KEY_UP:
        return UP;
    case KEY_DOWN:
        return DOWN;
    case KEY_LEFT:
        return LEFT;
    case KEY_RIGHT:
        return RIGHT;
    case 'o':
        return O;
    case 'p':
        return P;
    case 'l':
        return L;
    case 'm':
        return M;
    case 27:
        if (getch() == ERR) {
            printf("27 PRESSED\n");
            return ESCAPE;
        }
    default:
        break;
    }
    return NONE;
}

extern "C" IDisplay *create(void) {
    return new NcursesDisplay;
}

extern "C" void destroy(IDisplay *display) {
    delete display;
}
}  // namespace arc
