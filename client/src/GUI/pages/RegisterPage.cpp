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

    loadPage();
    layoutLoader();

    this->setObjectName("TOTO");
    std::cout << "Nom: "<< this->objectName().toStdString() << std::endl;
}

// LOADERS

void Client::GUI::RegisterPage::loadPage()
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

    _signButton->setFlat(true);
}

void Client::GUI::RegisterPage::labelLoader()
{
    _imgLogo = std::make_unique<QImage>(LOGO_PATH);
    _textLabel = std::make_unique<QLabel>();
    _labelLogo = std::make_unique<QLabel>();
    _labelPageName = std::make_unique<QLabel>();

    _labelLogo->setPixmap(QPixmap::fromImage(*_imgLogo));
    _labelLogo->setToolTip("logo du babel des boss du jeu");
    _labelPageName->setText("Babel :: Register Page");
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

    _delim["horizontal"]->setFrameShape(QFrame::HLine);
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
    _layout->addWidget(_labelPageName.get(), 0, 4, 3, 10);
    _layout->addWidget(_delim["horizontal"].get(), 3, 0, 1, WIDTH / 20 + 1);
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

void Client::GUI::RegisterPage::createAccount()
{
    emit changePage(CONTACTS);
}

void Client::GUI::RegisterPage::signIn()
{
    emit changePage(LOGIN);
}

#include "moc_RegisterPage.cpp"
