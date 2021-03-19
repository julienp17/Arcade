/*
** EPITECH PROJECT, 2021
** arcade [WSL: Ubuntu-20.04]
** File description:
** DLLoader
*/

#ifndef INC_DLLOADER_HPP_
#define INC_DLLOADER_HPP_

#include <string>

namespace arc {
template <typename T>
class DLLoader {
 public:
    const char *entryPointName = "entryPoint";

    /**
     * @brief Construct a new DLLoader object
     * 
     */
    DLLoader(void)
        : _handle(nullptr), _instance(nullptr) {}

    /**
     * @brief Construct a new DLLoader object
     * 
     * @param filename The path to the library to load
     */
    explicit DLLoader(const char *filename);

    /**
     * @brief Destroy the DLLoader object
     * 
     */
    ~DLLoader(void);

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
    void load(const char *filename);
    void *_handle;
    T *_instance;
};
}  // namespace arc


#endif  // INC_DLLOADER_HPP_
