/*
** EPITECH PROJECT, 2021
** MessageManager.cpp
** File description:
** MessageManager
*/

#ifndef MessageManager_h
#define MessageManager_h

#include <algorithm>
#include "ContactManager.hpp"

class MessageManager {
    public:
        MessageManager();
        ~MessageManager();
        std::deque<std::string> getHistory(const std::string &sender, const std::string &rec);
        void newMessage(const std::string &sender, const std::string &rec, const std::string &data);
    protected:
    private:
        Database _db;
};

#endif /* !MessageManager_h */
