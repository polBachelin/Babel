/*
** EPITECH PROJECT, 2021
** MessageManager.cpp
** File description:
** MessageManager
*/

#include "MessageManager.hpp"

MessageManager::MessageManager() : _db("db/database.db")
{
    _db.createTable("Message", "ID INTEGER PRIMARY KEY AUTOINCREMENT," \
                "SENDER TEXT NOT NULL," \
                "RECEIVER TEXT NOT NULL," \
                "DATA TEXT NOT NULL");
}

MessageManager::~MessageManager()
{
}

std::deque<std::string> MessageManager::getHistory(const std::string &sender, const std::string &rec)
{
    auto tmp = _db.custom("SELECT * FROM Message WHERE (SENDER=\'" + sender + "\' AND RECEIVER=\'" + rec + "\') OR (SENDER=\'" + rec + "\' AND RECEIVER=\'" + sender + "\')");
    std::deque<std::string> res;

    for (int i = 0; i < tmp.ac; i++) {
        if (tmp.c_name[i] == "ID") {
            res.push_back(tmp.av[i] + "\n" + tmp.av[i + 1] + "\n" + tmp.av[i + 2] + "\n" + tmp.av[i + 3] + "\n");
        }
    }
    return res;
}

void MessageManager::newMessage(const std::string &sender, const std::string &rec, const std::string &data)
{
    std::string res = data;

    
    std::replace(res.begin(), res.end(), '\'', ' ');
    std::replace(res.begin(), res.end(), '\"', ' ');
    _db.insert("Message", "SENDER, RECEIVER, DATA", "\'" + sender + "\', \'" + rec + "\', \'" + res + "\'");
}