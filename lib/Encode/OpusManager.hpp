/*
** EPITECH PROJECT, 2021
** Babel
** File description:
** OpusManager
*/

#ifndef OPUSMANAGER_HPP_
#define OPUSMANAGER_HPP_

#include "IEncodeManager.hpp"
#include "OpusException.hpp"
#include "opus.h"

#define CHANNELS (2)

class OpusManager : public IEncodeManager {
	public:
		OpusManager();
		~OpusManager() override;

        void setBitRate(const int &bitRate) override;
        void setSamplingRate(const int &samplingRate) override;
        void setComplexity(const int &complexity) override;
		void initDecoder() override;
        void initEncoder() override;
        int encode(unsigned char *output, float *input, int frameSize, std::size_t outputSize) override;
        int decode(const unsigned char *input, float *output, int frameSize, std::size_t intputSize) override;
	protected:
		int _bitRate;
		int _samplingRate;
		int _complexity;
		OpusEncoder *_encoder;
		OpusDecoder *_decoder;
		opus_int32 _err;
		opus_int32 _decoderErr;

};

#endif /* !OPUSMANAGER_HPP_ */
