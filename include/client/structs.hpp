/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-killian.vallette
** File description:
** structs
*/

#ifndef STRUCTS_HPP
#define STRUCTS_HPP

#include <string>

#define MAGIC 388474

namespace Client {

    struct ClientInfos {
        std::string username;
        std::string password;
        std::string userToCall;
        std::string ip;
        std::string port;
    };

    typedef struct packet {
        int magic;
        int code;
        int data_size;
        char data[2048] = {0};
    } packet_t;

}

#endif /* STRUCTS_HPP */
