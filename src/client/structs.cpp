#include "structs.hpp"

std::ostream &operator<<(std::ostream &out, const Client::ClientInfos_t &info)
{
    out <<  std::endl <<"---Infos---" << std::endl
        << "MyUsername:" << info.username << std::endl
        << "PortTCP:" << info.port << std::endl
        << "myIp:" << info.myIp << std::endl
        << "MyAudioPort:" << std::to_string(info.audioPort) << std::endl
        << "caller:" << info.userToCall << std::endl
        << "callerIp:" << info.callerIp << std::endl
        << "callerAudioPort:" << std::to_string(info.callerAudioPort) << std::endl
        << "currentData:" << info.currentData << std::endl
        << std::endl;
    return out;
}
