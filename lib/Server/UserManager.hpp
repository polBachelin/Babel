/*
** EPITECH PROJECT, 2021
** UserManager.cpp
** File description:
** UserManager
*/

#ifndef UserManager_h
#define UserManager_h

#include "ContactManager.hpp"
#include <asio.hpp>

class UserManager {
    public:
        UserManager();
        ~UserManager();
        int login(const std::string &, const std::string &);
        int newUser(const std::string &, const std::string &);
        ContactManager getContactManager() const;
        const std::string &getName() const;
    protected:
    private:
        Database _db;
        ContactManager _cm;
        std::string _name;
        bool _isLog = false;
};

#endif /* !UserManager_h */
