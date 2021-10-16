/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-killian.vallette
** File description:
** structs
*/

#ifndef STRUCTS_HPP
#define STRUCTS_HPP

#include <string>
#include <iostream>
#include <ostream>

#define MAGIC 388474

namespace Client {

    struct ClientInfos_t
    {
        std::string username;
        std::string password;
        std::string userToCall;
        std::string callerIp;
        std::string myIp;
        std::string port;
        std::string currentData;
        unsigned short callerAudioPort = 0;
        unsigned short audioPort = 0;
        bool callHost = false;
    };


    typedef struct packet {
        int magic;
        int code;
        int data_size;
        char data[2048] = {0};
    } packet_t;

}

std::ostream &operator<<(std::ostream &out, const Client::ClientInfos_t &info);

#endif /* STRUCTS_HPP */
