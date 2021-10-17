/*
** EPITECH PROJECT, 2021
** Babel
** File description:
** portAduoMain
*/

#include "PortAudioManager.hpp"
#include <unistd.h>

int main(void)
{
	PortAudioManager i;
	int buffSize = 3 * i.getSampleRate() * 2 * sizeof(float);
	float *sample = new float[buffSize];

	sleep(2);
	i.retrieveInputBytes(sample, i.getSampleRate());
	i.feedBytesToOutput(sample, i.getSampleRate());
	sleep(2);
}