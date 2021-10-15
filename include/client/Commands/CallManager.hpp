/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-killian.vallette
** File description:
** CallManager
*/

#ifndef CALLMANAGER_HPP_
#define CALLMANAGER_HPP_

#include <UdpClient.hpp>
#include "PortAudioManager.hpp"
#include "OpusManager.hpp"
#include <vector>
#include <iostream>
#include <memory>
#include <ctime>
#include <cstring>
#include <netinet/in.h>
#include <sys/types.h>

namespace Client
{
    namespace Managers
    {
        typedef std::unordered_map<std::string, std::time_t> callers_t;
        class CallManager : public QObject
        {
            Q_OBJECT

            public:
                CallManager(const std::string &myIp);
                ~CallManager();
                void connectToHost();
                void addPair(const std::string &ip);
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
                const unsigned short _audioPort = 6000;
                std::string _contactIp;
                const std::string _myIp;
                bool _inCall = false;
                float *_inputBuffer;
                float *_outputBuffer;
                int _frameSize;
                int _inputBufferSize;
                std::shared_ptr<OpusManager> _encoderManager;
                std::shared_ptr<PortAudioManager> _soundManager;
        };
    }
}
#endif /* !CALLMANAGER_HPP_ */
