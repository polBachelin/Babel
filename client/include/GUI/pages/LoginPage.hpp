/*
** EPITECH PROJECT, 2021
** Babel
** File description:
** LoginPage
*/

#ifndef DEF_MAFENETRE
#define DEF_MAFENETRE

#include "APage.hpp"

namespace Client {
namespace GUI {

class LoginPage : public APage
{
    Q_OBJECT

    public:
        LoginPage(ClientInfos infos, QWidget *parent = nullptr);
        ~LoginPage() = default;

        // member functions
        void initConnections() override;
        void loadPage() override;
        void layoutLoader() override;

        // widgtet loaders
        void delimLoader();
        void labelLoader();
        void formLoader();
        void btnLoader();

    public slots:
        void changeWidth(int width);
        void changeUsername(QString);
        void changePassword(QString);
        void signIn();
        void createAccount();

    private:
        // Layout
        std::unique_ptr<QGridLayout> _layout;

        // Widgets
        std::unique_ptr<QImage> _imgLogo;
        std::unique_ptr<QLabel> _labelLogo;
        std::unique_ptr<QLabel> _labelPageName;
        std::unique_ptr<QLabel> _emptyLabel;
        std::unique_ptr<QLabel> _textLabel;
        std::unique_ptr<QPushButton> _registerButton;

        // FORM
        std::unique_ptr<QLineEdit> _usernameForm;
        std::unique_ptr<QLabel> _errorUsername;
        std::unique_ptr<QLineEdit> _passwordForm;
        std::unique_ptr<QLabel> _errorPassword;
        std::unique_ptr<QPushButton> _signButton;

        // member variables
        std::string _username;
        std::string _password;
        bool _formError;
};

}}

#endif
