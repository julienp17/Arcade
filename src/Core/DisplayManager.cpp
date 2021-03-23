/*
** EPITECH PROJECT, 2021
** arcade [WSL: Ubuntu-20.04]
** File description:
** DisplayManager
*/

#include <dirent.h>
#include <errno.h>
#include <string.h>
#include "DisplayManager.hpp"
#include "Error.hpp"

namespace arc {
DisplayManager::DisplayManager() {
}

DisplayManager::~DisplayManager()
{
}

bool isDisplayLibrary(const std::string &filename) {
    return (
        filename.find("sdl") != std::string::npos
        || filename.find("ncurses") != std::string::npos);
}

void DisplayManager::loadLibraries(void) {
    DIR *dir = NULL;
    struct dirent *ent = NULL;
    ssize_t i = 0;

    dir = opendir(this->_libDir.c_str());
    if (dir == NULL)
        // TODO(julien) : create another exception for this error
        throw DLError(strerror(errno));
    while ((ent = readdir(dir)) != NULL) {
        if (ent->d_type == DT_REG && isDisplayLibrary(ent->d_name))
            _paths[i++] = _libDir + ent->d_name;
    }
    if (closedir(dir) == -1)
        throw DLError(strerror(errno));
}
}  // namespace arc
