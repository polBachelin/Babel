/*
** EPITECH PROJECT, 2021
** Babel
** File description:
** ConfigFileParser
*/

#ifndef CONFIGFILEPARSER_HPP_
#define CONFIGFILEPARSER_HPP_

#include <memory>
#include <regex>
#include <string>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <utility>
#include <iostream>
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
	#include <Bdirent.h>
	#include <Bunistd.h>
#else
	#include <dirent.h>
	#include <unistd.h>
#endif
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
