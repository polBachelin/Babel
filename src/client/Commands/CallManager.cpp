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
    //connect(_soundManager, outputAvailable, this, onReadAudioData);
    //connect(_soundManager, inputAvailable, this, sendAudioData);
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
    std::cout << "SendAudio: memset OK..." << std::endl;
    _soundManager->retrieveInputBytes(_inputBuffer, 480);
    std::cout << "SendAudio: retrieveBytes OK..." << std::endl;
    int compressedSize = _encoderManager->encode(compressedBuffer, _inputBuffer, 480, _inputBufferSize);
    std::cout << "SendAudio: encode OK... " << compressedSize << std::endl;
    audioPacket = createAudioPacket(compressedBuffer, compressedSize, std::time(nullptr));
    std::cout << "SendAudio: createAudioPacket OK..." << std::endl;
    ptr = reinterpret_cast<char *>(&audioPacket);
    dataPacket.port = _audioPort;
    dataPacket.data = ptr;
    std::cout <<  "Infos Caller" <<std::to_string(dataPacket.port) << dataPacket.data << std::endl;
    for (auto &pair : _pairs) {
        dataPacket.host = pair.first;
        _udpClient->send(dataPacket);
    }
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
    if (audioPacket->timestamp < _pairs[dataPacket.host])
        return;
    _pairs[dataPacket.host] = audioPacket->timestamp;
    _encoderManager->decode(audioPacket->data, _outputBuffer, 512, audioPacket->sizeOfData);
    _soundManager->feedBytesToOutput(_outputBuffer, 512);
}

void CallManager::beginCall(const std::vector<std::string> &pairs)
{
    std::cout << "BEGIN CALL" << std::endl;
    this->_inCall = true;
    this->_soundManager->startInputStream();
    this->_soundManager->startOutputStream();
    this->_udpClient->connectToHost(_ip);
    std::cout << "Connect to client caller..." << _ip << std::endl;
    for(auto &pair : pairs)
        _pairs.emplace(pair, 0);
    std::cout << "Emplace finished..." << std::endl;
    this->sendAudioData();
    std::cout << "Send data OK..." << std::endl;
}

void CallManager::endCall()
{
    this->_inCall = false;
    this->_udpClient->disconnect();
}

#include "moc_CallManager.cpp"