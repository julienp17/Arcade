/*
** EPITECH PROJECT, 2021
** arcade [WSL: Ubuntu-20.04]
** File description:
** DLManager
*/

#ifndef LIB_CORE_INC_DLMANAGER_HPP_
#define LIB_CORE_INC_DLMANAGER_HPP_

#include <memory>
#include <filesystem>
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
    virtual ~DLManager(void) {}

    /**
     * @brief Loads the previous dynamic library
     */
    void prev(void) {
        if (_i == 0)
            _i = _libs.size() - 1;
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
     * @param libName Name of the library to set, always in lowercase
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
        return _libs[_i].get()->get();
    }

    typedef std::shared_ptr<DLLoader<T>> DLPtr;
    typedef std::vector<DLPtr> DLPtrVec;

 private:
    /**
     * @brief Checks if a filename is compliant to an arcade dynamic library
     * filename
     *
     * A filename is considered compliant if it starts with "arcade_" and has
     * the extension ".so". Moreover, we pass to the function a vector of
     * library names to only load certain libraries. This is used to
     * differentiate display and game libraries.
     * @param libNames Names of the libraries to load
     * @param filename Name of the file to check
     * @return True if the filename is compliant
     * @return False if the filename is not compliant
     */
    bool libMatches(const std::vector<std::string> &libNames,
                    const std::string &filename) {
        auto startsWith = [](const std::string &str, const std::string &toFind){
            if (str.rfind(toFind, 0) == 0)
                return true;
            return false;
        };
        auto endsWith = [](const std::string &str, const std::string &toFind) {
            if (str.length() < toFind.length())
                return false;
            return (str.compare(str.length() - toFind.length(), toFind.length(),
                    toFind) == 0);
        };
        if (!startsWith(filename, std::string(_libDir + "arcade_"))
            || !endsWith(filename, ".so"))
            return false;
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
        for (auto &file : std::filesystem::directory_iterator(_libDir))
            if (file.is_regular_file() && libMatches(libNames, file.path()))
                _libs.push_back(DLPtr(new DLLoader<T>(file.path())));
    }

    // TODO(julien): find a way to not make this hardcoded!
    //* Path to the library directory
    const std::string _libDir = "./lib/";
    //* Index poiting to the current dynamic library
    size_t _i;
    // TODO(julien): maybe switch from a vector to a set ?
    //* Vector containing the loaded dynamic libraries
    DLPtrVec _libs;
};
}  // namespace arc

#endif  // LIB_CORE_INC_DLMANAGER_HPP_
