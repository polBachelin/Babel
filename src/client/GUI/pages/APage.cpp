/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-killian.vallette
** File description:
** APage
*/

#include "APage.hpp"

Client::GUI::APage::APage(ClientInfos_t infos, QWidget *parent) : QWidget(parent) ,_infos(infos)
{
}

void Client::GUI::APage::setClientInfos_t(const ClientInfos_t &infos)
{
    _infos = infos;
}

std::vector<std::string> convertCurrentData(std::string data, const char sep)
{
	// std::cout << "Convert Current Data [" << data << "]";
    std::replace(data.begin(), data.end(), sep, ' ');
    std::istringstream ss(data);
    std::string word;
    std::vector<std::string> words;

    while (ss >> word)
        words.push_back(word);
    return words;
}

std::ostream &operator<<(std::ostream &os, const Client::packet_t &pck)
{
    std::vector<std::string> data(convertCurrentData(std::string(pck.data), '\n'));

	os << "packet.magic     : " << pck.magic << std::endl;
	os << "packet.code      : " << pck.code << std::endl;
	os << "packet.data_size : " << pck.data_size << std::endl;
	os << "packet.data      : [";
    for (auto it = data.begin(); it != data.end(); it++) {
        os << *it << ((it == data.end()) ? "]" : ", ") << std::endl;
    }
	return os;
}

#include "moc_APage.cpp"
