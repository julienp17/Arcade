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
/** @class DLLoaderError
 * @brief Errors related to loading dynamic libraries
 */
class DLLoaderError : public DLError {
 public:
    DLLoaderError(void)
        : DLError(std::string("loader:") + dlerror()) {}
    explicit DLLoaderError(std::string const &message)
        : DLError(std::string("loader: ") + message) {}
};

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
        libDtor dtor = NULL;

        dtor = reinterpret_cast<libDtor>(dlsym(_handle, dtorName));
        if (dtor != NULL)
            dtor(_instance);
        dlclose(_handle);
    }

    /**
     * @brief Get the library's instance
     *
     * @return A pointer to the library class
     */
    T *get(void) const {
        return _instance;
    }

 private:
    //* Name of the entry point function of each library
    const char *ctorName = "create";
    //* Name of the delete function of each library
    const char *dtorName = "destroy";

    //* Type of class factory constructor
    typedef T *(*libCtor)(void);

    //* Type of class factory destructor
    typedef void (*libDtor)(T *);

    /**
     * @brief Loads the handle and the instance of the library
     *
     * @param filename The path to the library to load
     */
    void load(const std::string &filename) {
        libCtor ctor = NULL;

        _handle = dlopen(filename.c_str(), RTLD_NOW);
        if (_handle == NULL)
            throw DLLoaderError();
        ctor = reinterpret_cast<libCtor>(dlsym(_handle, ctorName));
        if (ctor == NULL)
            throw DLLoaderError();
        _instance = ctor();
        if (_instance == nullptr)
            throw DLLoaderError(filename + ": constructor failed");
    }

    //* Handle to the library in memory
    void *_handle;
    //* Pointer to the instance of the library class
    T *_instance;
};
}  // namespace arc


#endif  // LIB_CORE_INC_DLLOADER_HPP_
