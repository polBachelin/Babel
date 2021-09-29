/*
** EPITECH PROJECT, 2021
** UserManager.cpp
** File description:
** UserManager
*/

#ifndef UserManager_h
#define UserManager_h

#include "ContactManager.hpp"

class UserManager {
    public:
        UserManager();
        ~UserManager();
        int login(const std::string &, const std::string &);
        int new_user(const std::string &, const std::string &);
        const ContactManager &GetContactManager();
    protected:
    private:
        ContactManager _cm;
        Database _db;
        std::string _name;
        bool _isLog = false;
};

#endif /* !UserManager_h */
