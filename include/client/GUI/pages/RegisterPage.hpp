/*
** EPITECH PROJECT, 2021
** Babel
** File description:
** RegisterPage
*/

#ifndef DEF_REGISTERPAGE
#define DEF_REGISTERPAGE

#include "APage.hpp"

namespace Client {
namespace GUI {

class RegisterPage : public APage
{
    Q_OBJECT

    public:
        RegisterPage(ClientInfos_t infos, QWidget *parent = nullptr);
        ~RegisterPage() = default;

        // member functions
        void initConnections() override;
        void loadPage() override;
        void layoutLoader() override;
        void onPage() override;

        // widgtet loaders
        void delimLoader();
        void labelLoader();
        void formLoader();
        void btnLoader();

    public slots:
        void validRegister(ClientInfos_t);
        void wrongRegister(ClientInfos_t);
        void changeWidth(int width);
        void changeUsername(QString);
        void changePassword(QString);
        void changeConfirmPassword(QString);
        void createAccount();
        void signIn();

    private:
        // Layout
        std::unique_ptr<QGridLayout> _layout;

        // Widgets
        std::unique_ptr<QImage> _imgLogo;
        std::unique_ptr<QLabel> _labelLogo;
        std::unique_ptr<QLabel> _labelPageName;
        std::unique_ptr<QLabel> _emptyLabel;
        std::unique_ptr<QLabel> _textLabel;
        std::unique_ptr<QPushButton> _signButton;

        // FORM
        std::unique_ptr<QLineEdit> _usernameForm;
        std::unique_ptr<QLabel> _errorUsername;
        std::unique_ptr<QLineEdit> _passwordForm;
        std::unique_ptr<QLabel> _errorPassword;
        std::unique_ptr<QLineEdit> _confirmPasswordForm;
        std::unique_ptr<QLabel> _errorConfirmPassword;
        std::unique_ptr<QPushButton> _registerButton;

        // member variables
        std::string _username;
        std::string _password;
        std::string _confirmPassword;
        bool _formError;
};

}}

#endif
