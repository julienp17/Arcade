/*
** EPITECH PROJECT, 2021
** arcade [WSL: Ubuntu-20.04]
** File description:
** DLManager
*/

#ifndef INC_DLMANAGER_HPP_
#define INC_DLMANAGER_HPP_

#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <vector>
#include <string>
#include "DLLoader.hpp"
#include "Error.hpp"

namespace arc {
/** @class DLManager
 * @brief Container of dynamic libraries
 */
template <typename T>
class DLManager {
 public:
    // TODO(tristan): switch from giving a vector of names to a config file
    /**
     * @brief Loads matching dynamic libraries from the lib directory
     *
     * @param libNames Vector containing the name of the libraries to load
     * @example DLManager("OpenGL", "SDL2", "Ncurses")
     */
    explicit DLManager(const std::vector<std::string> &libNames) {
        _i = 0;
        this->loadLibs(libNames);
    }

    /**
     * @brief Destroy the Display Manager object
     */
    ~DLManager(void) {}

    /**
     * @brief Loads the previous dynamic library
     */
    void prev(void) {
        if (_i == 0)
            _i == _libs.size() - 1;
        else
            _i--;
    }

    /**
     * @brief Loads the next dynamic library
     */
    void next(void) {
        _i++;
        if (_i >= _libs.size())
            _i = 0;
    }

    /**
     * @brief Sets the current dynamic library
     *
     * @param libName Name of the library to set
     * @example set("sdl2")
     */
    void set(const std::string &libName) {
        for (auto it = _libs.begin() ; it != _libs.end() ; it++) {
            if (*it.get().getName() == libName) {
                _i = std::distance(_libs.begin(), it);
                return;
            }
        }
        throw DLError("Couldn't find library named " + libName);
    }

    /**
     * @brief Get the current instance of the loaded dynamic library
     *
     * @return A pointer to the instance of the loaded dynamic library
     */
    T *get(void) {
        return _libs[_i].get();
    }

 private:
    bool libMatches(const std::vector<std::string> &libNames,
                    const std::string &filename) {
        // TODO(julien): check if file respects regex arcade_*.so
        for (auto it = libNames.begin() ; it != libNames.end() ; it++)
            if (filename.find(*it) != std::string::npos)
                return true;
        return false;
    }

    /**
     * @brief Loads matching dynamic libraries from the lib directory
     *
     * @param libNames Vector containing the name of the libraries to load
     */
    void loadLibs(const std::vector<std::string> &libNames) {
        DIR *dir = NULL;
        struct dirent *ent = NULL;

        dir = opendir(_libDir.c_str());
        if (dir == NULL)
            throw DLError(strerror(errno));
        while ((ent = readdir(dir)) != NULL) {
            if (ent->d_type == DT_REG && libMatches(libNames,
                                                    std::string(ent->d_name)))
                _libs.push_back(DLLoader<T>(ent->d_name));
        }
        if (closedir(dir) == -1)
            throw DLError(strerror(errno));
    }

    // TODO(julien): find a way to not make this hardcoded!
    //* Path to the library directory
    const std::string _libDir = "./lib/";
    //* Index poiting to the current dynamic library
    size_t _i;
    // TODO(julien): maybe switch from a vector to a set ?
    //* Vector containing the loaded dynamic libraries
    std::vector<DLLoader<T>> _libs;
};
}  // namespace arc

#endif  // INC_CORE_DLMANAGER_HPP_
