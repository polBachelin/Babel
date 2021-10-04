/*
** EPITECH PROJECT, 2021
** ContactManager.cpp
** File description:
** ContactManager
*/

#include "ContactManager.hpp"

ContactManager::ContactManager() : _db("db/database.db"), _tableName("Contact")
{
    _db.createTable("Contact", "ID INTEGER PRIMARY KEY AUTOINCREMENT," \
                                "NAME TEXT NOT NULL," \
                                "FRIEND TEXT NOT NULL");
}

ContactManager::ContactManager(const std::string &name) : _db("db/database.db"), _myName(name), _tableName("Contact")
{
    _db.createTable("Contact", "ID INTEGER PRIMARY KEY AUTOINCREMENT," \
                                "NAME TEXT NOT NULL," \
                                "FRIEND TEXT NOT NULL");
}

ContactManager::~ContactManager()
{
    _db.close();
}


void ContactManager::addContact(const std::string &new_c, const std::string &your_name)
{
    _db.insert(_tableName, "NAME, FRIEND", "\'" + your_name + "\', \'" + new_c + "\'");
}

void ContactManager::addContact(const std::string &new_c)
{
    if (!_myName.empty())
        _db.insert(_tableName, "NAME, FRIEND", "\'" +  _myName + "\', \'" + new_c + "\'");
}

std::string ContactManager::getContactList()
{
    auto tmp = _db.custom("SELECT * FROM " + _tableName + " WHERE NAME=\'" + _myName + "\' OR FRIEND=\'" +_myName + "\'");
    std::string res; 

    for (int i = 0; i < tmp.ac; i++) {
        if (tmp.c_name[i] == "ID") {
            if (tmp.av[i + 1] == _myName) {
                res += tmp.av[i + 2] + "\n";
            }
            else if (tmp.av[i + 2] == _myName) {
                res += tmp.av[i + 1] + "\n";
            }
        }
    }
    return res;
}

std::string ContactManager::getContactList(const std::string &your_name)
{
    auto tmp = _db.custom("SELECT * FROM " + _tableName + " WHERE NAME=\'" + your_name + "\' OR FRIEND=\'" + your_name + "\'");
    std::string res; 

    for (int i = 0; i < tmp.ac; i++) {
        if (tmp.c_name[i] == "ID") {
            if (tmp.av[i + 1] == your_name) {
                res += tmp.av[i + 2] + "\n";
            }
            else if (tmp.av[i + 2] == your_name) {
                res += tmp.av[i + 1] + "\n";
            }
        }
    }
    return res;
}

void ContactManager::setName(const std::string &name)
{
    _myName = name;
}