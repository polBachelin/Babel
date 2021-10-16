/*
** EPITECH PROJECT, 2021
** UserManager.cpp
** File description:
** UserManager
*/

#ifndef UserManager_h
#define UserManager_h

#include "MessageManager.hpp"
#include <asio.hpp>

class UserManager {
    public:
        UserManager();
        ~UserManager();
        int login(const std::string &, const std::string &);
        int newUser(const std::string &, const std::string &);
        ContactManager getContactManager() const;
        MessageManager getMessageManager() const;
        std::string getName() const;
        void logoutUser();
        bool isLog();
    protected:
    private:
        Database _db;
        MessageManager _mm;
        ContactManager _cm;
        std::string _name;
        bool _isLog = false;
};

#endif /* !UserManager_h */
