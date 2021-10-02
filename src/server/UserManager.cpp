/*
** EPITECH PROJECT, 2021
** UserManager.cpp
** File description:
** UserManager
*/

#include "UserManager.hpp"

UserManager::UserManager() : _db("db/database.db"), _cm()
{
    _db.createTable("User", "ID INTEGER PRIMARY KEY AUTOINCREMENT," \
                    "USERNAME TEXT NOT NULL," \
                    "PASSWD TEXT NOT NULL");
}

UserManager::~UserManager()
{
    _db.close();
    _isLog = false;
}

int UserManager::login(const std::string &name, const std::string &passwd)
{
    auto tmp = _db.custom("SELECT USERNAME, PASSWD FROM User WHERE USERNAME=\'" + name + "\'");
    std::string res;

    if (tmp.ac >= 2 && tmp.av[1] == passwd) {
        _name = name;
        _cm.setName(_name);
        _isLog = true;
        std::cout << "Login successful" << std::endl;
    } else {
        std::cerr << "Invalid Login" << std::endl;
        _isLog = false;
        return false;
    }
    return true;
}

int UserManager::new_user(const std::string &name, const std::string &passwd)
{
    int tag = 0;
    std::string tag_res;
    int return_value = 0;

    std::srand(time(NULL));
    tag = std::rand() % 1000;
    tag_res = name + "#" + std::to_string(tag);
    std::cout << "New User : " << tag_res << std::endl;
    return_value = _db.insert("User", "USERNAME, PASSWD", "\'" + tag_res + "\', \'" + passwd + "\'");
    if (return_value) {
        std::cerr << "Failed to register" << std::endl;
        return false;
    }
    _name = tag_res;
    _cm.setName(tag_res);
    _isLog = true;
    return true;
}

const ContactManager &UserManager::GetContactManager()
{
    return _cm;
}

const std::string &UserManager::GetName()
{
    return _name;
}