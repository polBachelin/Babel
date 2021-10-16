/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-killian.vallette
** File description:
** CallManager
*/

#ifndef CALLMANAGER_HPP_
#define CALLMANAGER_HPP_

#include "UdpClient.hpp"
#include "PortAudioManager.hpp"
#include "OpusManager.hpp"
#include <vector>
#include <iostream>
#include <memory>
#include <ctime>
#include <cstring>
#include <netinet/in.h>
#include <sys/types.h>
#include <unordered_map>
#include <vector>

namespace Client
{
    namespace Managers
    {
        typedef std::unordered_map<std::string, std::pair<unsigned short, std::time_t>> callers_t;
        class CallManager : public QObject
        {
            Q_OBJECT

            public:
                CallManager(const std::string &myIp, const unsigned short audioPort);
                ~CallManager();
                void connectToHost();
                void addPair(const std::string &ip, unsigned short port);
                unsigned char *createAudioPacket(unsigned char *compressedBuff, int buffSize, std::time_t time);
                void beginCall();
                void endCall();

            signals:
                void sendData();
            public slots:
                void sendAudioData();
                void onReadAudioData();

            private:
                std::unique_ptr<Client::Network::UDPClient> _udpClient;
                callers_t _pairs;
                const int _magicNum = 1234;
                std::string _contactIp;
                const std::string _myIp;
                const unsigned short _audioPort;
                bool _inCall = false;
                float *_inputBuffer;
                float *_outputBuffer;
                int _frameSize;
                int _inputBufferSize;
                QTimer *_timer;
                std::shared_ptr<OpusManager> _encoderManager;
                std::shared_ptr<PortAudioManager> _soundManager;
        };
    }
}
#endif /* !CALLMANAGER_HPP_ */
