/*
** EPITECH PROJECT, 2021
** Babel
** File description:
** main
*/

#include <iostream>
#include "ISoundManager.hpp"
#include "IEncodeManager.hpp"
#include "DLLoader.hpp"
#include "ConfigFileParser.hpp"
#include "Error.hpp"
#include <unordered_map>

#define SAMPLE_RATE  (44100)
#define FRAMES_PER_BUFFER (512)
#define NUM_SECONDS     (5)

int main(void)
{
    std::unordered_map<ConfigFileParser::LIB_TYPE, std::vector<std::string>> _libs = ConfigFileParser::parseFile();

    std::shared_ptr<ISoundManager> ptr = DLLoader<ISoundManager>::getEntryPoint(_libs[ConfigFileParser::LIB_TYPE::SOUND].front());
    std::shared_ptr<IEncodeManager> encod = DLLoader<IEncodeManager>::getEntryPoint(_libs[ConfigFileParser::LIB_TYPE::ENCODE].front());
    
    if (ptr) {
        try {
            ptr->startInputStream();
            ptr->startOutputStream();
            std::cout << "==== Recording now ! ====" << std::endl;
            sleep(5);
            float *t = new float[SAMPLE_RATE * NUM_SECONDS * 2 * sizeof(float)];
            std::memset(t, 0, SAMPLE_RATE * NUM_SECONDS * 2 * sizeof(float));
            ptr->retrieveInputBytes(t, SAMPLE_RATE);
            ptr->feedBytesToOutput(t, SAMPLE_RATE * 3);
            //ptr->feedBytesToOutput(t, SAMPLE_RATE);
            sleep(5);
            std::cout << "-------------\n";
            // std::cout << "==== Playing audio ! ====" << std::endl;
        } catch (std::exception &e) {
            std::cout << e.what() << std::endl;
        }
    }
    return 0;
}