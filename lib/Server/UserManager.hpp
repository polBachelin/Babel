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

#define MAGIC 388474

typedef struct packet_info {
    int magic;
    int code;
    int data_size;
} packet_info_t;

typedef struct packet {
    int magic;
    int code;
    int data_size;
    char data[2048] = {0};
} packet_t;


class UserManager {
    public:
        UserManager(asio::ip::tcp::socket &s);
        ~UserManager();
        int login(const std::string &, const std::string &);
        int new_user(const std::string &, const std::string &);
        const ContactManager &GetContactManager();
        const std::string &GetName();
        asio::ip::tcp::socket &getSock();
    protected:
    private:
        asio::ip::tcp::socket &_sock;
        Database _db;
        ContactManager _cm;
        std::string _name;
        bool _isLog = false;
};

#endif /* !UserManager_h */
