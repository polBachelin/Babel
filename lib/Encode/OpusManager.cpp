/*
** EPITECH PROJECT, 2021
** Babel
** File description:
** OpusManager
*/

#include "OpusManager.hpp"

// extern "C"
// {
//     std::shared_ptr<IEncodeManager> entryPoint()
//     {
//         return std::make_shared<OpusManager>();
//     }
// }

OpusManager::OpusManager() : _bitRate(0), _samplingRate(0), _complexity(0), _encoder(nullptr), _decoder(nullptr)
{
}

OpusManager::~OpusManager()
{
	if (_encoder)
		opus_encoder_destroy(_encoder);
	if (_decoder)
		opus_decoder_destroy(_decoder);
}

void OpusManager::setBitRate(const int &bitRate) 
{
	_bitRate = bitRate;
}

void OpusManager::setSamplingRate(const int &samplingRate) 
{
	_samplingRate = samplingRate;
}

void OpusManager::setComplexity(const int &complexity) 
{
	_complexity = complexity;
}

void OpusManager::initDecoder()
{
	if (_decoder)
		return;
	_decoder = opus_decoder_create(_samplingRate, CHANNELS, &_decoderErr);
	if (_decoderErr == OPUS_OK) {
		opus_decoder_ctl(_decoder, OPUS_SET_BITRATE(_bitRate));
	} else {
		_decoder = nullptr;
		throw OpusException("Could not create opus decoder");
	}
}

void OpusManager::initEncoder()
{
	if (_encoder)
		return;
	_encoder = opus_encoder_create(_samplingRate, CHANNELS, OPUS_APPLICATION_VOIP, &_err);
	if (_err == OPUS_OK) {
		opus_encoder_ctl(_encoder, OPUS_SET_BITRATE(_bitRate));
	} else {
		_encoder = nullptr;
		throw OpusException("Could not create opus encoder");
	}
}

int OpusManager::encode(unsigned char *output, float *input, int frameSize, std::size_t outputSize)
{
	if (!_encoder)
		return -1;
	if ((_err = opus_encode_float(_encoder, input, frameSize, output, outputSize)))
		return _err;
	else {
		std::cerr << "Failed to encode : " << std::to_string(_err) << std::endl;
		return -1;
	}	
}

int OpusManager::decode(const unsigned char *input, float *output, int frameSize, std::size_t intputSize)
{
	if (!_decoder)
		return -1;
	if((_err = opus_decode_float(_decoder, input, intputSize, output, frameSize, 0)))
		return _err;
	else {
		std::cerr << "Failed to decode : " << std::to_string(_err) << std::endl;
		return -1;
	}
}
