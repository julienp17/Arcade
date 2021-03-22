/*
** EPITECH PROJECT, 2021
** arcade [WSL: Ubuntu-20.04]
** File description:
** DLLoader
*/

#include <dlfcn.h>
#include "DLLoader.hpp"
#include "Error.hpp"

template <typename T>
arc::DLLoader<T>::DLLoader(const char *filename) {
    this->load(filename);
}

template <typename T>
arc::DLLoader<T>::~DLLoader(void) {
    if (_handle != NULL && dlclose(_handle) != 0)
        throw DLLError(dlerror());
}

template <typename T>
void arc::DLLoader<T>::load(const char *filename) {
    // TODO(julien): check if file ends with .so
    _handle = dlopen(filename, RTLD_LAZY);
    if (_handle == NULL)
        throw DLLError(dlerror());
    _instance = dlsym(_handle, entryPointName);
    if (_instance == NULL)
        throw DLLError(dlerror());
}
