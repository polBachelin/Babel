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
#include "structs.hpp"

#define LOGO_PATH       "./assets/babelLogo_48x48.png"
#define PROFILE48_PATH  "./assets/profile_48x48.png"
#define PROFILE96_PATH  "./assets/profile_96x96.png"
#define BACKGROUND_PATH "./assets/background.png"

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

class APage : public QWidget
{
    Q_OBJECT

    public:
        APage(ClientInfos infos, QWidget *parent = nullptr);
        ~APage() = default;

        // member functions
        virtual void initConnections() = 0;
        virtual void loadPage() = 0;
        virtual void layoutLoader() = 0;

    signals:
        void changePage(pageNames name);


    protected:
        std::unique_ptr<QGridLayout> _layout;
        QWidget *_parent;
        ClientInfos _infos;
};

}
}

#endif /* !APAGE_HPP_ */
