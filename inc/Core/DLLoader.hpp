/*
** EPITECH PROJECT, 2021
** arcade [WSL: Ubuntu-20.04]
** File description:
** DLLoader
*/

#ifndef INC_CORE_DLLOADER_HPP_
#define INC_CORE_DLLOADER_HPP_

#include <dlfcn.h>
#include <string>
#include "Error.hpp"

namespace arc {
template <typename T>
class DLLoader {
 public:
    const char *entryPointName = "getInstance";
    const char *dtorName = "destroyInstance";

    /**
     * @brief Construct a new DLLoader object
     */
    DLLoader(void) : _handle(nullptr), _instance(nullptr) {}

    /**
     * @brief Construct a new DLLoader object
     *
     * @param filename The path to the library to load
     */
    explicit DLLoader(const char *filename) {
        this->load(filename);
    }

    /**
     * @brief Destroy the DLLoader object
     *
     */
    ~DLLoader(void) {
        if (_handle != NULL) {
            ((void (*)(T *)) dlsym(_handle, dtorName))(_instance);
            if (dlclose(_handle) != 0)
                throw DLError(dlerror());
        }
    }

    /**
     * @brief Get the Instance object
     *
     * @return T*
     */
    inline T *getInstance(void) {
        return _instance;
    }

 private:
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
    void *_handle;
    T *_instance;
};
}  // namespace arc


#endif  // INC_CORE_DLLOADER_HPP_
