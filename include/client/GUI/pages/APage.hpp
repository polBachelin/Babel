/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-killian.vallette
** File description:
** APage
*/

#ifndef APAGE_HPP_
#define APAGE_HPP_

#include <QApplication>
#include <QWidget>
#include <QtWidgets>
#include <QPushButton>
#include <memory>
#include <QLineEdit>
#include <QFormLayout>
#include <QSlider>
#include <QtCore/QObject>
#include <QPixmap>
#include <vector>
#include <iostream>
#include <cstring>
#include <unordered_map>
#include "structs.hpp"
#include <bits/stdc++.h>

#define LOGO_PATH       "./assets/babelLogo_48x48.png"
#define PROFILE48_PATH  "./assets/profile_48x48.png"
#define PROFILE96_PATH  "./assets/profile_96x96.png"
#define BACKGROUND_PATH "./assets/background.png"
#define LOGOGIF_PATH    "./assets/animatedLogo.gif"

#define VALIDATE_PATH "./assets/validate_48x48.png"
#define REFUSE_PATH   "./assets/refuse_48x48.png"
#define CALLON_PATH   "./assets/callOn_48x48.png"
#define CALLOFF_PATH  "./assets/callOff_48x48.png"
#define SOUNDON_PATH  "./assets/soundOn_48x48.png"
#define SOUNDOFF_PATH "./assets/soundOff_48x48.png"
#define MICON_PATH    "./assets/micOn_48x48.png"
#define MICOFF_PATH   "./assets/micOff_48x48.png"

#define WIDTH  800
#define HEIGHT 600

namespace Client {
namespace GUI {

    enum pageNames
    {
        LOGIN,
        REGISTER,
        CONTACTS,
        CALL
    };

    enum signal_e
    {
        Elogin = 0,
        Elogout = 10,
        Eregister = 1,
        Eaddcontact = 2,
        Eacceptinvitation = 112,
        EcallX = 3,
        Erefuseincomingcall = 203,
        Easkcontactlist = 4
    };

    enum receivedSignal_e
    {
        EloginSuccessful = 100,
        EloginFailed = 200,
        EregisterSuccessful = 101,
        EregisterFailed = 201,
        EinvitationReceive = 12,
        EcontactExist = 102,
        EcontactAddFailed = 202,
        EincomingCall = 303,
        EUserForCallNotFound = 603,
        EcallWasRefused = 203,
        EcontactList = 4
    };

class APage : public QWidget
{
    Q_OBJECT

    public:
        APage(ClientInfos_t infos, QWidget *parent = nullptr);
        ~APage() = default;

        // member functions
        virtual void initConnections() = 0;
        virtual void loadPage() = 0;
        virtual void layoutLoader() = 0;
        virtual void onPage() = 0;

        void setClientInfos_t(const ClientInfos_t &);

    signals:
        void changePage(pageNames name, ClientInfos_t);
        void checkCommand(ClientInfos_t, signal_e);

    protected:
        std::unique_ptr<QGridLayout> _layout;
        ClientInfos_t _infos;
};


}
}

std::vector<std::string> convertCurrentData(std::string, const char);
std::ostream &operator<<(std::ostream &, const Client::packet_t &);

#endif /* !APAGE_HPP_ */
