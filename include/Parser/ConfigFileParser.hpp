/*
** EPITECH PROJECT, 2021
** Babel
** File description:
** ConfigFileParser
*/

#ifndef CONFIGFILEPARSER_HPP_
#define CONFIGFILEPARSER_HPP_

#include <memory>
#include <unistd.h>
#include <regex>
#include <string>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <utility>
#include <iostream>
#include <dirent.h>
#include <sys/types.h>
#include <unordered_map>

#include "FileException.hpp"

class ConfigFileParser {
	public:
	    enum LIB_TYPE {
            SOUND,
            NETWORK,
			ENCODE
        };

        static std::unordered_map<LIB_TYPE, std::vector<std::string>> parseFile(const std::string &fileName = "./lib/configFile.babel");
		static std::pair<ConfigFileParser::LIB_TYPE, std::vector<std::string>> parseLib(const std::string &line, ConfigFileParser::LIB_TYPE type, std::ifstream &stream);
		static void removeComment(std::string &line);
};

#endif /* !CONFIGFILEPARSER_HPP_ */
