/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-killian.vallette
** File description:
** CallManager
*/

#include "CallManager.hpp"

using namespace Client::Managers;

CallManager::CallManager(const std::string &myIp, const unsigned short audioPort)
: QObject(), _myIp(myIp), _audioPort(audioPort)
{
    _udpClient = std::make_unique<Client::Network::UDPClient>();
    _soundManager = std::make_shared<PortAudioManager>();
    _encoderManager = std::make_shared<OpusManager>();
    _frameSize = _soundManager->getInputChannels() * sizeof(float);
    _inputBufferSize =  3 * _soundManager->getSampleRate() * _frameSize;
    _inputBuffer = new float[_inputBufferSize];
    _outputBuffer = new float[_inputBufferSize];
    _encoderManager->setBitRate(64000);
    _encoderManager->setSamplingRate(_soundManager->getSampleRate());
    _encoderManager->initDecoder();
    _encoderManager->initEncoder();
    _timer = new QTimer();
    _timer->setInterval(1);
    QObject::connect(_timer, SIGNAL(timeout()), this, SLOT(sendAudioData()));
    // QObject::connect(_udpClient.get(), SIGNAL(getDataFromUDP()), this, SLOT(onReadAudioData()));
    // QObject::connect(this, SIGNAL(sendData()), this, SLOT(sendAudioData()));
}

CallManager::~CallManager()
{
}

void CallManager::addPair(const std::string &ip, unsigned short port)
{
    //std::cout << "Add Pair: " << ip << ":" << port << std::endl;
    _pairs[ip] = std::make_pair<unsigned short, std::time_t>((unsigned short)port, std::time_t(NULL));
}

unsigned char *CallManager::createAudioPacket(unsigned char *compressedBuff, int buffSize, std::time_t time)
{
    unsigned char *res = new unsigned char[buffSize * sizeof(unsigned char) + sizeof(std::time_t) + sizeof(int)];
    uintptr_t ptr = reinterpret_cast<uintptr_t >(res);
    // uint32_t networkBuffSize = htonl(buffSize);
    // uint32_t networkTime = htonl(time);

    //std::cout << "[createAudioPacket] buffSize : " << buffSize << std::endl;
    //std::cout << "[createAudioPacket] networkBuffSize : " << buffSize << std::endl;
    //std::cout << "[createAudioPacket] networkTime : " << time << std::endl;

    std::memcpy((res), &time, sizeof(std::time_t));
    std::memcpy((res + sizeof(std::time_t)), &buffSize, sizeof(int));
    std::memcpy((res + sizeof(std::time_t) + sizeof(int)), compressedBuff, buffSize * sizeof(unsigned char));
    return res;
}

void CallManager::sendAudioData()
{
    Client::Network::packetUDP_t dataPacket;

    while (_soundManager->getBytesInInput() >= 480) {
        unsigned char *audioPacket;
        unsigned char *compressedBuffer = new unsigned char[_inputBufferSize];
        std::memset(compressedBuffer, 0, _inputBufferSize);
        _soundManager->retrieveInputBytes(_inputBuffer, 480);
        std::cout << "-----SENDING AUDIO DATA----\n";
        double max = 0;
        double average = 0.0;
        double val = 0;
        for(int i=0; i<480; i++ )
        {
            val = _inputBuffer[i];
            if( val < 0 ) val = -val; /* ABS */
            if( val > max )
            {
                max = val;
            }
            average += val;
        }

        average = average / (double)480;
        std::cout << "[INPUT] : AVERAGE = " << average << " MAX : " << max << std::endl;
        int compressedSize = _encoderManager->encode(compressedBuffer, _inputBuffer, 480, _inputBufferSize);
        //std::cout << "[INPUT] COMPRESSED BUFFER IN HEXA " << hex((char)compressedBuffer[0]) << std::endl;
        audioPacket = createAudioPacket(compressedBuffer, compressedSize, std::time(nullptr));
        dataPacket.port = _audioPort;
        dataPacket.host = _myIp;
        dataPacket.data = audioPacket;
        // std::cout << "Message: " << (char *)dataPacket.data << std::endl;
        std::cout << "---------------------------\n";

        //std::cout << "Checking data Packet networkBuffSize should be same as [createAudioPacket] one :  " << *ptrBuffSize << std::endl;
        //std::cout <<  "Infos from Caller: " << std::to_string(dataPacket.port) << std::endl;
        for (auto &i : _pairs)
            _udpClient->send(dataPacket, i.first, i.second.first, compressedSize);

        delete [] compressedBuffer;
        delete [] audioPacket;
    }
    onReadAudioData();
}

void CallManager::onReadAudioData()
{
    Client::Network::packetUDP_t dataPacket;
    unsigned char *compressed;
    unsigned char *ptr;

    while (this->_udpClient->hasPendingDatagram() || _udpClient->getNbData() < 100) {
        _udpClient->recieveDatagram();
    }
    while ((dataPacket = _udpClient->getData()).magicNum != 0) {
        std::cout << "-----READING AUDIO DATA----\n";
        if (dataPacket.magicNum == 0) {
            std::cout << "WRONG MAGIC NUMBER\n";
            return;
        }
        ptr = dataPacket.data;
        std::time_t timestamp;
        std::memcpy(&timestamp, ptr, sizeof(std::time_t));
        int buffSize;
        std::memcpy(&buffSize, (ptr + sizeof(std::time_t)), sizeof(int));
        // std::cout << "Network Time : " << timestamp << std::endl;
        //std::cout << "Network BuffSize : " << buffSize << std::endl;
        compressed = new unsigned char[buffSize];
        std::memset(compressed, 0, buffSize);
        std::memcpy(compressed, (ptr + sizeof(std::time_t) + sizeof(buffSize)), buffSize * sizeof(unsigned char));
        auto outputBuffer = new float[_inputBufferSize];
        std::cout << "DECODE SIZE = " << _encoderManager->decode(compressed, outputBuffer, 480, buffSize) << std::endl;
        double max = 0;
        double average = 0.0;
        double val = 0;
        for(int i=0; i<480; i++ )
        {
            val = _inputBuffer[i];
            if( val < 0 ) val = -val; /* ABS */
            if( val > max )
            {
                max = val;
            }
            average += val;
        }

        average = average / (double)480;
        std::cout << "[OUTPUT] : AVERAGE = " << average << " MAX : " << max << std::endl;
        std::cout << "---------------------------\n";
        _soundManager->feedBytesToOutput(outputBuffer, 480);
        delete [] outputBuffer;
    }
    //emit sendData();
}

void CallManager::connectToHost()
{
    std::cout << "UDP bind my IP : " << _myIp << std::endl;
    this->_udpClient->connectToHost(_myIp, _audioPort);
    this->_inCall = true;
    _timer->start();
}

void CallManager::beginCall()
{
    std::cout << "BEGIN CALL" << std::endl;
    std::cout << "Connect to client caller..." << _myIp << std::endl;
    this->connectToHost();
    //TODO: set UP audio ????
}

void CallManager::endCall()
{
    this->_inCall = false;
    this->_udpClient->disconnect();
    _pairs.clear();

    //TODO: disable audio ????
    QObject::disconnect(_timer, SIGNAL(timeout()), this, SLOT(sendAudioData()));
    QObject::disconnect(this, SIGNAL(sendData()), this, SLOT(sendAudioData()));
}

#include "moc_CallManager.cpp"
