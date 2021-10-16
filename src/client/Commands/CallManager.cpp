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
    _encoderManager->setBitRate(10);
    _encoderManager->setSamplingRate(_soundManager->getSampleRate());
    _encoderManager->initDecoder();
    _encoderManager->initEncoder();
    _soundManager->startInputStream();
    _soundManager->startOutputStream();
    QObject::connect(_udpClient.get(), SIGNAL(getDataFromUDP()), this, SLOT(onReadAudioData()));
    QObject::connect(this, SIGNAL(sendData()), this, SLOT(sendAudioData()));
}

CallManager::~CallManager()
{
}

void CallManager::addPair(const std::string &ip, unsigned short port)
{
    std::cout << "Add Pair: " << ip << ":" << port << std::endl;
    _pairs[ip] = std::make_pair<unsigned short, std::time_t>((unsigned short)port, std::time_t(NULL));
}

unsigned char *CallManager::createAudioPacket(unsigned char *compressedBuff, int buffSize, std::time_t time)
{
    unsigned char *res = new unsigned char[buffSize * sizeof(unsigned char) + sizeof(uint32_t) + sizeof(uint32_t)];
    uintptr_t ptr = reinterpret_cast<uintptr_t >(res);
    uint32_t networkBuffSize = htonl(buffSize);
    uint32_t networkTime = htonl(time);

    std::cout << "[createAudioPacket] buffSize : " << buffSize << std::endl;
    std::cout << "[createAudioPacket] networkBuffSize : " << networkBuffSize << std::endl;
    std::cout << "[createAudioPacket] networkTime : " << networkTime << std::endl;
    std::memcpy((void *)ptr, &networkTime, sizeof(uint32_t));
    ptr += sizeof(uint32_t);
    std::memcpy((void *)ptr, &networkBuffSize, sizeof(uint32_t));
    ptr += sizeof(uint32_t);
    std::memcpy((void *)ptr, compressedBuff, buffSize * sizeof(compressedBuff));
    return res;
}

void CallManager::sendAudioData()
{
    Client::Network::packetUDP_t dataPacket;
    unsigned char *audioPacket;
    unsigned char *compressedBuffer = new unsigned char[_inputBufferSize];

    std::memset(compressedBuffer, 0, _inputBufferSize);
    _soundManager->retrieveInputBytes(_inputBuffer, 480);
    int compressedSize = _encoderManager->encode(compressedBuffer, _inputBuffer, 480, _inputBufferSize);
    audioPacket = createAudioPacket(compressedBuffer, compressedSize, std::time(nullptr));

    dataPacket.port = _audioPort;
    dataPacket.host = _myIp;
    dataPacket.data = audioPacket;
    dataPacket.dataSize = compressedSize;

    std::cout << "-----SENDING AUDIO DATA----\n";
    std::cout << "BuffSize : " << compressedSize << std::endl;
    qDebug() << "Message: " << QString::fromStdString(std::string((char *)dataPacket.data));
    uint32_t *ptrTime = reinterpret_cast<uint32_t *>(dataPacket.data + sizeof(uint32_t));
    std::cout << "Checking data Packet networkBuffSize should be same as [createAudioPacket] one :  " << *ptrTime << std::endl;
    std::cout << "---------------------------\n"; 
    std::cout <<  "Infos from Caller: " << std::to_string(dataPacket.port) << std::endl;

    std::cout << "PrepareMyPacket: "<< dataPacket << std::endl;

    for (auto &i : _pairs)
        _udpClient->send(dataPacket, i.first, i.second.first);

    delete [] compressedBuffer;
    delete [] audioPacket;
}

void CallManager::onReadAudioData()
{
    Client::Network::packetUDP_t dataPacket = this->_udpClient->getData();
    unsigned char *compressed;
    uintptr_t ptr = reinterpret_cast<uintptr_t>(dataPacket.data);

    // ? changer la condition pour checker le timestamp
    //if (audioPacket->timestamp < _pairs[dataPacket.host])
        //return;
    uint32_t *timestampPtr = reinterpret_cast<uint32_t *>(ptr);
    //ptr += sizeof(uint32_t);
    uint32_t *buffSizePtr = reinterpret_cast<uint32_t *>(ptr + sizeof(timestampPtr));
    //if (dataPacket.timestamp < _pairs[dataPacket.host].second)
    //    return;
    _pairs[dataPacket.host].second = std::time_t(NULL);
    std::time_t timestamp = ntohl(*timestampPtr);
    (void)timestamp;
    int buffSize = ntohl(*buffSizePtr);
    std::cout << dataPacket << std::endl;
    std::cout << "-----READING AUDIO DATA----\n";
    std::cout << "Network Time : " << *timestampPtr << std::endl;
    std::cout << "Network BuffSize : " << *buffSizePtr << std::endl;
    std::cout << "BuffSize : " << buffSize << std::endl;
    std::cout << "---------------------------\n";

    //if (_pairs.find(dataPacket.host) == _pairs.end())
    addPair(dataPacket.host, dataPacket.port);
    //compressed = new unsigned char[buffSize];
    //std::memcpy(compressed, (void *)(ptr + sizeof(std::time_t) + sizeof(buffSize)), buffSize * sizeof(compressed));

    // _encoderManager->decode(compressed, _outputBuffer, 480, buffSize);
    // _soundManager->feedBytesToOutput(_outputBuffer, 480);
    emit sendData();
}

void CallManager::connectToHost()
{
    std::cout << "UDP bind my IP : " << _myIp << std::endl;
    this->_udpClient->connectToHost(_myIp, _audioPort);
    this->_inCall = true;
    this->sendAudioData();
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

    QObject::disconnect(this, SIGNAL(sendData()), this, SLOT(sendAudioData()));
}

#include "moc_CallManager.cpp"
