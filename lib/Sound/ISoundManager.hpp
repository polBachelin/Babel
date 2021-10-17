/*
** EPITECH PROJECT, 2021
** Babel
** File description:
** ISoundManager
*/

#ifndef ISOUNDMANAGER_HPP_
#define ISOUNDMANAGER_HPP_

#include <vector>
#include <string>

class ISoundManager {
    public:
        virtual ~ISoundManager() = default;
        virtual void setMicMute(bool mute) = 0;
        virtual bool isMicMuted() = 0;
        virtual void setOutputMute(bool mute) = 0;
        virtual bool isOutputMuted() = 0;
        virtual void setDefaultInputDevice() = 0;
        virtual void setDefaultOutputDevice() = 0;
        virtual void abortOutputStream() = 0;
        virtual void abortInputStream() = 0;
        virtual std::vector<std::string> getInputDeviceNames() const = 0;
        virtual std::vector<std::string> getOutputDeviceNames() const = 0;
        virtual bool isInputStreamActive() = 0;
        virtual bool isOutputStreamActive() = 0;
        virtual void startInputStream() = 0;
        virtual void startOutputStream() = 0;
        virtual void closeOutputStream() = 0;
        virtual void closeInputStream() = 0;
        virtual int getBytesInInput() = 0;
        virtual int getSampleRate() = 0;
        virtual size_t getInputChannels() const = 0;
        virtual size_t getOutputChannels() const = 0;
        virtual int retrieveInputBytes(float *sample, size_t len) = 0;
        virtual void feedBytesToOutput(float *sample, unsigned long len) = 0;
        virtual void loadDefaultDevices() = 0;
};

#endif /* !ISOUNDMANAGER_HPP_ */
