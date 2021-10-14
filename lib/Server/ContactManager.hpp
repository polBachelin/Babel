/*
** EPITECH PROJECT, 2021
** ContactManager.cpp
** File description:
** ContactManager
*/

#ifndef ContactManager_h
#define ContactManager_h

#include "DB/Database.hpp"

class ContactManager {
    public:
        ContactManager();
        ContactManager(const std::string &);
        ~ContactManager();
        void addContact(const std::string &new_c, const std::string &your_name);
        void addContact(const std::string &new_c);
        void setName(const std::string &);
        const std::string &getContactList();
        const std::string &getContactList(const std::string &your_name);
    protected:
    private:
        Database _db;
        std::string _myName;
        std::string _tableName;

};

#endif /* !ContactManager_h */
