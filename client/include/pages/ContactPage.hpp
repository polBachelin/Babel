/*
** EPITECH PROJECT, 2021
** Babel
** File description:
** ContactPage
*/

#ifndef DEF_CONTACTPAGE
#define DEF_CONTACTPAGE

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

#define LOGO_PATH "./assets/babelLogo_48x48.png"
#define CALL_PATH "./assets/acceptCall_48x48.png"
#define WIDTH     800
#define HEIGHT    600

class ContactPage : public QWidget
{
    Q_OBJECT

    public:
        // Ctor / Dtor
        ContactPage(QWidget *parent = nullptr);
        ~ContactPage() = default;

        // member functions
        void loadPage();
        void layoutLoader();

        // widgtet loaders
        void contactLoader();
        void delimLoader();
        void labelLoader();
        void callLoader();
        void formLoader();

        // event handlers
        void connexionHandler();

    public slots:
        void contactClicked();
        void callClicked();

    private:
        // Layout
        std::unique_ptr<QGridLayout> _layout;

        // Widgets
        std::unique_ptr<QImage> _imgLogo;
        std::unique_ptr<QPixmap> _imgCall;
        std::unique_ptr<QLabel> _labelLogo;
        std::unique_ptr<QLabel> _labelPageName;
        std::unique_ptr<QLabel> _labelContactName;
        std::unique_ptr<QLabel> _labelContactSelected;
        std::unique_ptr<QLabel> _labelCalling;
        std::unique_ptr<QPushButton> _call;
        std::unique_ptr<QLineEdit> _contactSearch;
        std::unique_ptr<QLineEdit> _writeMsg;

        // Widget lists
        std::map<std::string, std::unique_ptr<QFrame>> _delim;
        std::vector<std::shared_ptr<QPushButton>> _contacts;

        // member variables
        QSlider *   _m_slider;
        QWidget *   _parent;
        std::string _username;
        QString _contactSelected;
        bool _calling;
};

#endif
