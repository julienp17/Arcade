/*
** EPITECH PROJECT, 2021
** arcade [WSL: Ubuntu-20.04]
** File description:
** DisplayManager
*/

#ifndef INC_CORE_DISPLAYMANAGER_HPP_
#define INC_CORE_DISPLAYMANAGER_HPP_

#include <string>
#include "DLLoader.hpp"

namespace arc {
class DisplayManager {
 public:
    /**
     * @brief Default constructor for a new Display Manager object
     *
     * Loads paths of shared libraries without loading one
     */
    DisplayManager(void);

    /**
     * @brief Construct a new Display Manager object with a loaded library
     *
     * @param filename Path of the library to load
     */
    explicit DisplayManager(const std::string &filename);

    /**
     * @brief Destroy the Display Manager object
     */
    ~DisplayManager(void);

    /**
     * @brief Loads a display library
     *
     * @param filename Path of the library to load
     */
    void load(const std::string &filename);

    /**
     * @brief Loads the previous display library
     */
    void prev(void);

    /**
     * @brief Loads the next display library
     */
    void next(void);

    /**
     * @brief Get the current instance of the loaded shared library
     *
     * @return A pointer to the instance of the loaded shared library
     */
    IDisplay *get(void) {
        return _loader.getInstance();
    }

 private:
    const std::string _libDir = "./lib/";

    void loadLibraries(void);
    std::string _paths[3];
    DLLoader<IDisplay> _loader;
};
}  // namespace arc

#endif  // INC_CORE_DISPLAYMANAGER_HPP_
