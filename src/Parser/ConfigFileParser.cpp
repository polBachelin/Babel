/*
** EPITECH PROJECT, 2021
** Babel
** File description:
** ConfigFileParser
*/

#include "ConfigFileParser.hpp"

static const std::string SOUND_LIB = "SOUND_LIB:";
static const std::string NETWORK_LIB = "NETWORK_LIB:";
static const std::string ENCODE_LIB = "ENCODE_LIB:";

static void removeWhiteSpaces(std::string &str)
{
    str.erase(std::remove(str.begin(), str.end(), '\t'), str.end());
    str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
}

std::unordered_map<ConfigFileParser::LIB_TYPE, std::vector<std::string>> ConfigFileParser::parseFile(const std::string &fileName)
{
    std::string line = "";
    std::ifstream fileStream;
    std::unordered_map<ConfigFileParser::LIB_TYPE, std::vector<std::string>> res;

    fileStream.open(fileName);
    if (!fileStream.is_open())
        throw FileException(std::string("Could not open file : " + fileName));
    while (std::getline(fileStream, line)) {
        if (line.find(SOUND_LIB) != std::string::npos)
            res.insert(parseLib(line, ConfigFileParser::SOUND, fileStream));
        if (line.find(NETWORK_LIB) != std::string::npos) {
            res.insert(parseLib(line, ConfigFileParser::NETWORK, fileStream));
        }
        if (line.find(ENCODE_LIB) != std::string::npos) {
            res.insert(parseLib(line, ConfigFileParser::ENCODE, fileStream));
        }
    }
    if (res.empty())
        throw FileException("No libraries found in file");
    return res;
}

std::pair<ConfigFileParser::LIB_TYPE, std::vector<std::string>> ConfigFileParser::parseLib(const std::string &line, ConfigFileParser::LIB_TYPE type, std::ifstream &stream)
{
    std::string c_line = "";
    std::vector<std::string> lib;
    std::pair<ConfigFileParser::LIB_TYPE, std::vector<std::string>> res;
    std::regex reg(".+libBabel_.+.so");

    if (line.find('{') == std::string::npos)
        throw FileException("Badly formatted configuration file on line " + line);
    while (c_line.find("}") == std::string::npos) {
        if (!std::getline(stream, c_line))
            throw FileException("No closing brackets found");
        removeWhiteSpaces(c_line);
        removeComment(c_line);
        if (std::regex_match(c_line, reg))
            lib.push_back(c_line);
    }
    res.first = type;
    res.second = lib;
    return res;
}

void ConfigFileParser::removeComment(std::string &line)
{
    if (line.find("#") != std::string::npos) {
        line = line.substr(0, line.find('#'));
    }
}