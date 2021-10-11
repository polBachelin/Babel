/*
** EPITECH PROJECT, 2021
** Babel
** File description:
** CallPage
*/

#ifndef DEF_CALLPAGE
#define DEF_CALLPAGE

#include "APage.hpp"

namespace Client {
namespace GUI {

class CallPage : public APage
{
    Q_OBJECT

    public:
        CallPage(ClientInfos infos, QWidget *parent = nullptr);
        ~CallPage() = default;

        // member functions
        void initConnections() override;
        void loadPage() override;
        void layoutLoader() override;
        void onPage() override;

        // widgtet loaders
        void delimLoader();
        void labelLoader();
        void btnLoader();
        void timerLoader();
        void inCall(bool);
        void incomingCall(bool);

    public slots:
        void soundOff();
        void soundOn();
        void micOff();
        void micOn();
        void callOff();
        void callOn();
        void updateTimer();

    private:
        // Layout
        std::unique_ptr<QGridLayout> _layout;

        // Widgets
        std::unique_ptr<QImage> _imgLogo;
        std::unique_ptr<QLabel> _labelLogo;
        std::unique_ptr<QImage> _imgProfile;
        std::unique_ptr<QLabel> _labelProfile;
        std::unique_ptr<QLabel> _labelPageName;
        std::unique_ptr<QLabel> _emptyLabel;
        std::unique_ptr<QLabel> _labelTimer;
        std::unique_ptr<QTimer> _timer;
        std::unique_ptr<QElapsedTimer> _eltimer;

        // Buttons
        std::unique_ptr<QPixmap> _imgCallOff;
        std::unique_ptr<QPushButton> _callOff;
        std::unique_ptr<QPixmap> _imgSoundOn;
        std::unique_ptr<QPushButton> _soundOn;
        std::unique_ptr<QPixmap> _imgSoundOff;
        std::unique_ptr<QPushButton> _soundOff;
        std::unique_ptr<QPixmap> _imgMicOn;
        std::unique_ptr<QPushButton> _micOn;
        std::unique_ptr<QPixmap> _imgMicOff;
        std::unique_ptr<QPushButton> _micOff;

        // Gif
        std::unique_ptr<QMovie> _gif;
        std::unique_ptr<QLabel> _labelGif;
        std::unique_ptr<QPixmap> _imgValidate;
        std::unique_ptr<QPushButton> _validate;
        std::unique_ptr<QPixmap> _imgRefuse;
        std::unique_ptr<QPushButton> _refuse;
        std::unique_ptr<QLabel> _labelContact;

        // member variables
        std::string _username;
        bool _calling;
};

}}

#endif
