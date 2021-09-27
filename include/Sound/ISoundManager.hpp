/*
** EPITECH PROJECT, 2021
** Babel
** File description:
** ISoundManager
*/

#ifndef ISOUNDMANAGER_HPP_
#define ISOUNDMANAGER_HPP_

class ISoundManager {
    public:
        virtual ~ISoundManager() = default;
        virtual int recordAudio() = 0;
        virtual int playAudio() = 0;
        virtual bool isMicMuted() = 0;
        virtual bool isOutputMuted() = 0;
        virtual bool isStreamActive() = 0;
};

#endif /* !ISOUNDMANAGER_HPP_ */
