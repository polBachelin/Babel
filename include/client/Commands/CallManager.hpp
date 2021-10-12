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


namespace Client
{
    namespace Managers
    {
        class CallManager : public QObject
        {
            Q_OBJECT

            public:
                CallManager(const std::string &myIp);
                ~CallManager();
                void sendAudioData();
                 //TODO: paramètre input compressé
                void connectToHosts();
                Client::Network::audioPacket_t createAudioPacket(unsigned char *compressedBuff, int buffSize, std::time_t time);
                void beginCall(const std::vector<std::string> &pairs);
                void endCall();

            public slots:
                void onReadAudioData();


            private:
                std::unique_ptr<Client::Network::UDPClient> _udpClient;
                std::map<std::string, std::time_t> _pairs;
                const int _magicNum = 1234;
                const unsigned short _audioPort = 5000;
                const std::string _ip;
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
