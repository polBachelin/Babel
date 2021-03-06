/*
** EPITECH PROJECT, 2021
** Babel
** File description:
** LoginPage
*/

#include "LoginPage.hpp"

Client::GUI::LoginPage::LoginPage(ClientInfos_t infos, QWidget *parent) : APage(infos, parent)
{
    setFixedSize(WIDTH, HEIGHT);
    _formError = false;

    QObject::connect(parent, SIGNAL(validSignInResponse(ClientInfos_t)),
        this, SLOT(validSignIn(ClientInfos_t)));
    QObject::connect(parent, SIGNAL(wrongSignInResponse(ClientInfos_t)),
        this, SLOT(wrongSignIn(ClientInfos_t)));

    loadPage();
    layoutLoader();
}

// LOADERS

void Client::GUI::LoginPage::onPage()
{
}

void Client::GUI::LoginPage::loadPage()
{
    btnLoader();
    labelLoader();
    formLoader();
    delimLoader();
}

void Client::GUI::LoginPage::btnLoader()
{
    _signButton = std::make_unique<QPushButton>("Sign In");
    _registerButton = std::make_unique<QPushButton>("Create an account");

    _registerButton->setStyleSheet("QPushButton { text-decoration: underline; } QPushButton:hover { color: blue; text-decoration: underline; }");
    _registerButton->setFlat(true);
    _signButton->setDefault(true);
}

void Client::GUI::LoginPage::labelLoader()
{
    _imgLogo = std::make_unique<QImage>(LOGO_PATH);
    _textLabel = std::make_unique<QLabel>();
    _labelLogo = std::make_unique<QLabel>();
    _labelPageName = std::make_unique<QLabel>();
    _errorUsername = std::make_unique<QLabel>();
    _errorPassword = std::make_unique<QLabel>();

    _errorUsername->setStyleSheet("QLabel { color : red; }");
    _errorPassword->setStyleSheet("QLabel { color : red; }");
    _labelLogo->setPixmap(QPixmap::fromImage(*_imgLogo));
    _labelLogo->setToolTip("logo du babel des boss du jeu");
    _labelPageName->setText("Login Page");
    _labelPageName->setStyleSheet("QLabel { color : white; font-size: 30px;}");
    _textLabel->setText("or");
}

void Client::GUI::LoginPage::formLoader()
{
    _usernameForm = std::make_unique<QLineEdit>();
    _passwordForm = std::make_unique<QLineEdit>();

    _usernameForm->setPlaceholderText("Username");
    _passwordForm->setPlaceholderText("Password");
    _passwordForm->setEchoMode(QLineEdit::Password);
}

void Client::GUI::LoginPage::delimLoader()
{
}

void Client::GUI::LoginPage::layoutLoader()
{
    _emptyLabel = std::make_unique<QLabel>();
    _layout = std::make_unique<QGridLayout>();

    for (std::size_t i = 0; i < HEIGHT / 20; i++)
        _layout->addWidget(_emptyLabel.get(), i, 0);
    for (std::size_t i = 0; i < WIDTH / 20; i++)
        _layout->addWidget(_emptyLabel.get(), 0, i);
    _layout->addWidget(_labelLogo.get(), 0, 2, 3, 2);
    _layout->addWidget(_labelPageName.get(), 0, 15, 3, 10);

    _layout->addWidget(_errorUsername.get(), 9, 12, 4, 15); // -- error
    _layout->addWidget(_errorPassword.get(), 12, 12, 4, 15); // -- error
    _layout->addWidget(_usernameForm.get(), 10, 12, 4, 15);
    _layout->addWidget(_passwordForm.get(), 13, 12, 4, 15);

    _layout->addWidget(_signButton.get(), 18, 8, 2, 10);
    _layout->addWidget(_textLabel.get(), 18, 20, 2, 2);
    _layout->addWidget(_registerButton.get(), 18, 22, 2, 10);

    this->setLayout(_layout.get());
    initConnections();
}

// CONEXION -- EVENT HANDLER

void Client::GUI::LoginPage::initConnections()
{
    QObject::connect(_usernameForm.get(), SIGNAL(textChanged(QString)), this, SLOT(changeUsername(QString)));
    QObject::connect(_passwordForm.get(), SIGNAL(textChanged(QString)), this, SLOT(changePassword(QString)));
    QObject::connect(_signButton.get(), SIGNAL(clicked()), this, SLOT(signIn()));
    QObject::connect(_registerButton.get(), SIGNAL(clicked()), this, SLOT(createAccount()));
}

void Client::GUI::LoginPage::changeWidth(int width)
{
    this->setFixedSize(width, 100);
}

void Client::GUI::LoginPage::changeUsername(QString username)
{
    this->_username = username.toStdString();
}

void Client::GUI::LoginPage::changePassword(QString password)
{
    this->_password = password.toStdString();
}

void Client::GUI::LoginPage::signIn()
{
    _errorPassword->setText("");
    _errorUsername->setText("");
   if (_password.empty()) {
        _formError = true;
        _errorPassword->setText("password is empty");
    }
   if (_password.size() > 16) {
        _formError = true;
        _errorPassword->setText("password must have a maximum of 16 char");
    }
    if (_username.empty()) {
        _formError = true;
        _errorUsername->setText("username is empty");
    }
   if (_username.size() > 16) {
        _formError = true;
        _errorUsername->setText("username must have a maximum of 16 char");
    }

    if (_formError) {
        _formError = false;
        return;
    }

    _infos.username = _username;
    _infos.password = _password;

    this->setDisabled(true);
    emit checkCommand(_infos, Elogin);
}

void Client::GUI::LoginPage::validSignIn(ClientInfos_t info)
{
    std::cout << "GOTO - contact page" << std::endl << std::endl;

    _username = "";
    _password = "";
    _usernameForm->setText(_username.c_str());
    _passwordForm->setText(_password.c_str());

    this->setDisabled(false);
    emit changePage(CONTACTS, info);
}

void Client::GUI::LoginPage::wrongSignIn(ClientInfos_t info)
{
    (void)info;
    _errorPassword->setText("wrong password");
    _errorUsername->setText("wrong username");

    this->setDisabled(false);
}

void Client::GUI::LoginPage::createAccount()
{
    std::cout << "GOTO - register page" << std::endl << std::endl;

    _username = "";
    _password = "";
    _usernameForm->setText(_username.c_str());
    _passwordForm->setText(_password.c_str());
    _errorPassword->setText("");
    _errorUsername->setText("");

    emit changePage(REGISTER, _infos);
}

#include "moc_LoginPage.cpp"
