/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-killian.vallette
** File description:
** structs
*/

#ifndef STRUCTS_HPP
#define STRUCTS_HPP

#include <string>
#include <ostream>

#define MAGIC 388474

namespace Client {

    struct ClientInfos_t
    {
        friend std::ostream &operator<<(std::ostream &out, const ClientInfos_t &info)
    {
        out << "---Infos---\n"
        << "MyUsername:" << info.username << "\n"
        << "PortTCP:" << info.port << "\n"
        << "myIp:" << info.myIp << "\n"
        << "MyAudioPort:" << std::to_string(info.audioPort) << "\n"
        << "caller:" << info.userToCall << "\n"
        << "callerIp:" << info.callerIp << "\n"
        << "callerAudioPort:" << std::to_string(info.callerAudioPort) << "\n"
        << "currentData:" << info.currentData << "\n"
        << std::endl;
        return out;
    }
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

#endif /* STRUCTS_HPP */
