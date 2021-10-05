/*
** EPITECH PROJECT, 2021
** ContactManager.cpp
** File description:
** ContactManager
*/

#ifndef ContactManager_h
#define ContactManager_h

#include "Database.hpp"

class ContactManager {
    public:
        ContactManager();
        ContactManager(const std::string &);
        ~ContactManager();
        void addContact(const std::string &new_c, const std::string &your_name);
        void addContact(const std::string &new_c);
        void setName(const std::string &);
        std::string getContactList();
        std::string getContactList(const std::string &your_name);
    protected:
    private:
        Database _db;
        std::string _myName;
        std::string _tableName;

};

#endif /* !ContactManager_h */
