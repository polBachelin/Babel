/*
** EPITECH PROJECT, 2021
** Babel
** File description:
** DLLoader
*/

#ifndef DLLOADER_HPP_
#define DLLOADER_HPP_

#include <iostream>
#include <memory>
#include <cstring>
#include <dlfcn.h>

template<typename T>
class DLLoader {
    public:
        static std::shared_ptr<T> getEntryPoint(std::string filePath)
        {
            void *handle = NULL;
            std::shared_ptr<T> (*instance)(void);
            std::shared_ptr<T> ptr = NULL;
            const char *error = NULL;

            handle = dlopen(filePath.c_str(), RTLD_LAZY | RTLD_NODELETE | RTLD_GLOBAL);
            error = dlerror();
            if (!handle) {
                std::cerr << "Could not retrieve handle from filepath : " << filePath << std::endl << "Error is : " << error << std::endl;
                return nullptr;
            }
            *(void **)&instance = dlsym(handle, "entryPoint");
            error = dlerror();
            if (!instance) {
                std::cerr << "Could not retrieve instance from handler" << std::endl;
                return nullptr;
            }
            ptr = (instance)();
            dlclose(handle);
            return ptr;
        }
};

#endif /* !DLLOADER_HPP_ */
