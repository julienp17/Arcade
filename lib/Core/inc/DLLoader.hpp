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
    explicit DLLoader(const std::string &filename) {
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
     * @brief Get the library's instance
     *
     * @return A pointer to the library class
     */
    inline T *get(void) {
        return _instance;
    }

 private:
    //* Name of the entry point function of each library
    const char *entryPointName = "getInstance";
    //* Name of the delete function of each library
    const char *dtorName = "destroyInstance";

    //* Pointer to library constructor
    typedef T *(*libCtor)(void);

    /**
     * @brief Loads the handle and the instance of the library
     *
     * @param filename The path to the library to load
     */
    void load(const std::string &filename) {
        libCtor ctor = NULL;

        _handle = dlopen(filename.c_str(), RTLD_NOW);
        if (_handle == NULL)
            throw DLError(filename + ": " + dlerror());
        ctor = ((libCtor) dlsym(_handle, entryPointName));
        if (ctor == NULL)
            throw DLError(filename + ": " + dlerror());
        _instance = ctor();
        if (_instance == nullptr)
            throw DLError(filename + ": constructor failed");
    }

    //* Handle to the library in memory
    void *_handle;
    //* Pointer to the instance of the library class
    T *_instance;
};
}  // namespace arc


#endif  // LIB_CORE_INC_DLLOADER_HPP_
