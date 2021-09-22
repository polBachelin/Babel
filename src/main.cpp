/*
** EPITECH PROJECT, 2021
** Babel
** File description:
** main
*/

#include <iostream>
#include "ISoundManager.hpp"
#include "DLLoader.hpp"
#include "PortAudioManager.hpp"

int main(void)
{
    DLLoader<ISoundManager> loader;
    PortAudioManager ok;

    ok.recordAudio();
    return 0;
}