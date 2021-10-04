/*
** EPITECH PROJECT, 2021
** Babel
** File description:
** ContactPage
*/

#ifndef DEF_CONTACTPAGE
#define DEF_CONTACTPAGE

#include "APage.hpp"

namespace Client {
namespace GUI {

class ContactPage : public APage
{
    Q_OBJECT

    public:
        // Ctor / Dtor
        ContactPage(Client::ClientInfos infos, QWidget *parent = nullptr);
        ~ContactPage() = default;

        // member functions
        void initConnections() override;
        void loadPage() override;
        void layoutLoader() override;

        // widgtet loaders
        void contactLoader();
        void delimLoader();
        void labelLoader();
        void callLoader();
        void formLoader();

        // other functions
        void addOneContact(std::string);

    public slots:
        void contactClicked();
        void callClicked();
        void logOut();
        void searchContact(QString);
        void changeMsg(QString);

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
        std::unique_ptr<QLabel> _emptyLabel;
        std::unique_ptr<QPushButton> _call;
        std::unique_ptr<QLineEdit> _contactSearch;
        std::unique_ptr<QLineEdit> _writeMsg;

        // Widget lists
        std::map<std::string, std::unique_ptr<QFrame>> _delim;
        std::vector<std::shared_ptr<QPushButton>> _contacts;
        std::unique_ptr<QPushButton> _backButton;

        // member variables
        QSlider *   _m_slider;
        QWidget *   _parent;
        std::string _username;
        std::string _msg;
        std::string _search;
        QString _contactSelected;
        std::size_t _cid;
};

}}

#endif
