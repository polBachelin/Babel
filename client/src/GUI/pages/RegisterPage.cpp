/*
** EPITECH PROJECT, 2021
** Babel
** File description:
** RegisterPage
*/

#include "RegisterPage.hpp"

Client::GUI::RegisterPage::RegisterPage(ClientInfos infos, QWidget *parent) : APage(infos, parent)
{
    setFixedSize(WIDTH, HEIGHT);
    _formError = false;

    loadPage();
    layoutLoader();
}

// LOADERS

void Client::GUI::RegisterPage::loadPage()
    // this->setObjectName("TOTO");
    // std::cout << "Nom: "<< this->objectName().toStdString() << std::endl;

{
    btnLoader();
    labelLoader();
    formLoader();
    delimLoader();
}

void Client::GUI::RegisterPage::btnLoader()
{
    _registerButton = std::make_unique<QPushButton>("Register");
    _signButton = std::make_unique<QPushButton>("Log in");

    _signButton->setStyleSheet("QPushButton { text-decoration: underline; } QPushButton:hover { color: blue; text-decoration: underline; }");
    _signButton->setFlat(true);
    _registerButton->setDefault(true);
}

void Client::GUI::RegisterPage::labelLoader()
{
    _imgLogo = std::make_unique<QImage>(LOGO_PATH);
    _textLabel = std::make_unique<QLabel>();
    _labelLogo = std::make_unique<QLabel>();
    _labelPageName = std::make_unique<QLabel>();
    _errorUsername = std::make_unique<QLabel>();
    _errorPassword = std::make_unique<QLabel>();
    _errorConfirmPassword = std::make_unique<QLabel>();

    _errorUsername->setStyleSheet("QLabel { color : red; }");
    _errorPassword->setStyleSheet("QLabel { color : red; }");
    _errorConfirmPassword->setStyleSheet("QLabel { color : red; }");
    _labelLogo->setPixmap(QPixmap::fromImage(*_imgLogo));
    _labelLogo->setToolTip("logo du babel des boss du jeu");
    _labelPageName->setText("Register Page");
    _labelPageName->setStyleSheet("QLabel { color : white; font-size: 30px;}");
    _textLabel->setText("or");
}

void Client::GUI::RegisterPage::formLoader()
{
    _usernameForm = std::make_unique<QLineEdit>();
    _passwordForm = std::make_unique<QLineEdit>();
    _confirmPasswordForm = std::make_unique<QLineEdit>();

    _usernameForm->setPlaceholderText("Username");
    _passwordForm->setPlaceholderText("Password");
    _confirmPasswordForm->setPlaceholderText("confirm your password");
}

void Client::GUI::RegisterPage::delimLoader()
{
    _delim["horizontal"] = std::make_unique<QFrame>();

    _delim["horizontal"]->setFrameShadow(QFrame::Sunken);
    _delim["horizontal"]->setFrameShape(QFrame::HLine);
}

void Client::GUI::RegisterPage::layoutLoader()
{
    _emptyLabel = std::make_unique<QLabel>();
    _layout = std::make_unique<QGridLayout>();

    for (std::size_t i = 0; i < HEIGHT / 20; i++)
        _layout->addWidget(_emptyLabel.get(), i, 0);
    for (std::size_t i = 0; i < WIDTH / 20; i++)
        _layout->addWidget(_emptyLabel.get(), 0, i);
    _layout->addWidget(_labelLogo.get(), 0, 2, 3, 2);
    _layout->addWidget(_labelPageName.get(), 0, 15, 3, 10);
    // _layout->addWidget(_delim["horizontal"].get(), 3, 0, 1, WIDTH / 20 + 1);

    _layout->addWidget(_errorUsername.get(), 9, 12, 4, 15); // -- error
    _layout->addWidget(_errorPassword.get(), 12, 12, 4, 15); // -- error
    _layout->addWidget(_errorConfirmPassword.get(), 15, 12, 4, 15); // -- error
    _layout->addWidget(_usernameForm.get(), 10, 12, 4, 15);
    _layout->addWidget(_passwordForm.get(), 13, 12, 4, 15);
    _layout->addWidget(_confirmPasswordForm.get(), 16, 12, 4, 15);

    _layout->addWidget(_registerButton.get(), 21, 8, 2, 10);
    _layout->addWidget(_textLabel.get(), 21, 20, 2, 2);
    _layout->addWidget(_signButton.get(), 21, 21, 2, 10);

    this->setLayout(_layout.get());
    initConnections();
}

// CONEXION -- EVENT HANDLER

void Client::GUI::RegisterPage::initConnections()
{
    QObject::connect(_usernameForm.get(), SIGNAL(textChanged(QString)), this, SLOT(changeUsername(QString)));
    QObject::connect(_passwordForm.get(), SIGNAL(textChanged(QString)), this, SLOT(changePassword(QString)));
    QObject::connect(_confirmPasswordForm.get(), SIGNAL(textChanged(QString)), this, SLOT(changeConfirmPassword(QString)));
    QObject::connect(_registerButton.get(), SIGNAL(clicked()), this, SLOT(createAccount()));
    QObject::connect(_signButton.get(), SIGNAL(clicked()), this, SLOT(signIn()));
}

void Client::GUI::RegisterPage::changeWidth(int width)
{
    this->setFixedSize(width, 100);
}

void Client::GUI::RegisterPage::changeUsername(QString username)
{
    this->_username = username.toStdString();
}

void Client::GUI::RegisterPage::changePassword(QString password)
{
    this->_password = password.toStdString();
}

void Client::GUI::RegisterPage::changeConfirmPassword(QString password)
{
    this->_confirmPassword = password.toStdString();
}

void Client::GUI::RegisterPage::createAccount()
{
    _errorPassword->setText("");
    _errorUsername->setText("");
    _errorConfirmPassword->setText("");
    if (_password.empty()) {
        _formError = true;
        _errorPassword->setText("password is empty");
    }
    if (_username.empty()) {
        _formError = true;
        _errorUsername->setText("username is empty");
    }
    if (_confirmPassword.empty()) {
        _formError = true;
        _errorConfirmPassword->setText("confirm password is empty");
    }
    if (_password != _confirmPassword) {
        _formError = true;
        _errorConfirmPassword->setText("confirm password is different");
    }

    if (_formError) {
        _formError = false;
        return;
    }

    std::cout << "GOTO - contact page" << std::endl << std::endl;

    _username = "";
    _password = "";
    _confirmPassword = "";
    _usernameForm->setText(_username.c_str());
    _passwordForm->setText(_password.c_str());
    _confirmPasswordForm->setText(_confirmPassword.c_str());

    emit changePage(CONTACTS);
}

void Client::GUI::RegisterPage::signIn()
{
    std::cout << "GOTO - login page" << std::endl << std::endl;

    _username = "";
    _password = "";
    _confirmPassword = "";
    _usernameForm->setText(_username.c_str());
    _passwordForm->setText(_password.c_str());
    _confirmPasswordForm->setText(_confirmPassword.c_str());
    _errorPassword->setText("");
    _errorUsername->setText("");
    _errorConfirmPassword->setText("");

    emit changePage(LOGIN);
}

#include "moc_RegisterPage.cpp"
