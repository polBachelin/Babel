/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-killian.vallette
** File description:
** CallManager
*/

#include "CallManager.hpp"

using namespace Client::Managers;

CallManager::CallManager(const std::string &myIp) : QObject(), _ip(myIp)
{
    _udpClient = std::make_unique<Client::Network::UDPClient>();
    _soundManager = std::make_shared<PortAudioManager>();
    _encoderManager = std::make_shared<OpusManager>();
    _frameSize = _soundManager->getInputChannels() * sizeof(float);
    _inputBufferSize =  3 * _soundManager->getSampleRate() * _frameSize;
    _inputBuffer = new float[_inputBufferSize];
    _outputBuffer = new float[_inputBufferSize];
    _encoderManager->setBitRate(10);
    std::cout << "SAMPLE" << _soundManager->getSampleRate() << std::endl;
    _encoderManager->setSamplingRate(_soundManager->getSampleRate());
    _encoderManager->initDecoder();
    _encoderManager->initEncoder();
    //TODO: connect input to sendAudio + output to readAudio
    QObject::connect(_udpClient.get(), SIGNAL(getDataFromUDP()), this, SLOT(onReadAudioData()));
    QObject::connect(this, SIGNAL(sendData()), this, SLOT(sendAudioData()));
}

CallManager::~CallManager()
{
}

Client::Network::audioPacket_t CallManager::createAudioPacket(unsigned char *compressedBuff, int buffSize, std::time_t time)
{
    Client::Network::audioPacket_t audioPacket;

    audioPacket.timestamp = time;
    audioPacket.data = new unsigned char[buffSize];
    std::memcpy(audioPacket.data, compressedBuff, buffSize);
    audioPacket.sizeOfData = buffSize;
    return audioPacket;
}

void CallManager::sendAudioData()
{
    Client::Network::packetUDP_t dataPacket;
    Client::Network::audioPacket_t audioPacket;
    char *ptr;
    unsigned char *compressedBuffer = new unsigned char[_inputBufferSize];

    std::memset(compressedBuffer, 0, _inputBufferSize);
    _soundManager->retrieveInputBytes(_inputBuffer, 480);
    int compressedSize = _encoderManager->encode(compressedBuffer, _inputBuffer, 480, _inputBufferSize);
    audioPacket = createAudioPacket(compressedBuffer, compressedSize, std::time(nullptr));
    ptr = reinterpret_cast<char *>(&audioPacket);

    dataPacket.port = _audioPort;
    dataPacket.data = ptr;
    dataPacket.host = _ip;

    std::cout <<  "Infos from Caller: " << std::to_string(dataPacket.port) << dataPacket.data << std::endl;
    _udpClient->send(dataPacket);

    delete [] compressedBuffer;
    delete [] audioPacket.data;
}

void CallManager::onReadAudioData()
{

    Client::Network::packetUDP_t dataPacket = this->_udpClient->getData();
    auto *audioPacket = reinterpret_cast<Client::Network::audioPacket_t *>(dataPacket.data);

    if (audioPacket->magicNum != _magicNum) {
        std::cerr << "OVNI" << std::endl;
        return;
    }
    // ? changer la condition pour checker le timestamp
    //if (audioPacket->timestamp < _pairs[dataPacket.host])
        //return;
    //_pairs[dataPacket.host] = audioPacket->timestamp;
    _encoderManager->decode(audioPacket->data, _outputBuffer, 512, audioPacket->sizeOfData);
    _soundManager->feedBytesToOutput(_outputBuffer, 512);
}

void CallManager::connectToHost(const std::string &ip)
{
    this->_udpClient->connectToHost(ip);
    this->_inCall = true;
    this->_soundManager->startInputStream();
    this->_soundManager->startOutputStream();
    this->sendAudioData();
}

void CallManager::beginCall()
{
    std::cout << "BEGIN CALL" << std::endl;
    std::cout << "Connect to client caller..." << _ip << std::endl;
    this->connectToHost(_ip);
    this->sendAudioData();
    std::cout << "Send data OK..." << std::endl;
}

void CallManager::endCall()
{
    this->_inCall = false;
    this->_udpClient->disconnect();
    QObject::disconnect(this, SIGNAL(sendData()), this, SLOT(sendAudioData));
}

#include "moc_CallManager.cpp"