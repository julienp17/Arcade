/*
** EPITECH PROJECT, 2021
** arcade [WSL: Ubuntu-20.04]
** File description:
** DLLoader
*/

#ifndef LIB_CORE_INC_DLLOADER_HPP_
#define LIB_CORE_INC_DLLOADER_HPP_

#include <dlfcn.h>
#include <string>
#include "Error.hpp"

namespace arc {
/** @class DLLoader
 * @brief Encapsulation of a dynamic library
 */
template <typename T>
class DLLoader {
 public:
    /**
     * @brief Construct a new DLLoader object
     *
     * @param filename The path to the library to load
     */
    explicit DLLoader(const char *filename) {
        _handle = nullptr;
        _instance = nullptr;
        this->load(filename);
    }

    /**
     * @brief Destroy the DLLoader object
     *
     */
    ~DLLoader(void) {
        dlclose(_handle);
    }

    /**
     * @brief Get the Instance object
     *
     * @return T*
     */
    inline T *get(void) {
        return _instance;
    }

 private:
    const char *entryPointName = "getInstance";
    const char *dtorName = "destroyInstance";

    /**
     * @brief Loads the handle and the instance of the library
     *
     * @param filename The path to the library to load
     */
    void load(const char *filename) {
        // TODO(julien): check if file ends with .so
        _handle = dlopen(filename, RTLD_LAZY);
        if (_handle == NULL)
            throw DLError(dlerror());
        _instance = ((T *(*)(void)) dlsym(_handle, entryPointName))();
        if (_instance == NULL)
            throw DLError(dlerror());
    }

    //* Handle to the library in memory
    void *_handle;
    //* Pointer to an instance of the library class
    T *_instance;
};
}  // namespace arc


#endif  // LIB_CORE_INC_DLLOADER_HPP_
