/*
** EPITECH PROJECT, 2021
** Babel
** File description:
** portAduoMain
*/

#include "PortAudioManager.hpp"
#include "OpusManager.hpp"
#include <unistd.h>

int main(void)
{
	PortAudioManager i;
	int buffSize = 3 * i.getSampleRate() * 2 * sizeof(float);
	std::vector<unsigned char *> allBuffers;
	std::vector<int> allSizes;
	OpusManager a;
	float *decompressedSample;

	a.setBitRate(68000);
	a.setSamplingRate(i.getSampleRate());
	a.initDecoder();
	a.initEncoder();
	sleep(3);
	while (i.getBytesInInput() >= 480) {
		float *sample = new float[buffSize];
		unsigned char *compressed = new unsigned char[buffSize];
		i.retrieveInputBytes(sample, 480);
		int newSize = a.encode(compressed, sample, 480, buffSize);
		allSizes.push_back(newSize);
		allBuffers.push_back(compressed);
	}
	std::cout << "PLAYING AUDIO\n";
	decompressedSample = new float[buffSize];
	while (allBuffers.size() > 0) {
		std::memset(decompressedSample, 0, buffSize);
		int newSize = a.decode(allBuffers.front(), decompressedSample, 480, allSizes.front());
		i.feedBytesToOutput(decompressedSample, 480);
		allBuffers.erase(allBuffers.begin());
		allSizes.erase(allSizes.begin());
	}
	sleep(3);
}