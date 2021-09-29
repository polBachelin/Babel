#include "LoginPage.hpp"
#include <iostream>

Client::GUI::LoginPage::LoginPage(ClientInfos infos, QWidget *parent) : APage(infos, parent)
{
    setFixedSize(WIDTH, HEIGHT);

    loadPage();
    layoutLoader();

    this->setObjectName("TOTO");
    std::cout << "Nom: "<< this->objectName().toStdString() << std::endl;
}

// LOADERS

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

    _registerButton->setFlat(true);
}

void Client::GUI::LoginPage::labelLoader()
{
    _imgLogo = std::make_unique<QImage>(LOGO_PATH);
    _textLabel = std::make_unique<QLabel>();
    _labelLogo = std::make_unique<QLabel>();
    _labelPageName = std::make_unique<QLabel>();

    _labelLogo->setPixmap(QPixmap::fromImage(*_imgLogo));
    _labelLogo->setToolTip("logo du babel des boss du jeu");
    _labelPageName->setText("Babel :: Login Page");
    _textLabel->setText("or");
}

void Client::GUI::LoginPage::formLoader()
{
    _usernameForm = std::make_unique<QLineEdit>();
    _passwordForm = std::make_unique<QLineEdit>();

    _usernameForm->setPlaceholderText("Username");
    _passwordForm->setPlaceholderText("Password");
}

void Client::GUI::LoginPage::delimLoader()
{
    _delim["horizontal"] = std::make_unique<QFrame>();

    _delim["horizontal"]->setFrameShape(QFrame::HLine);
    _delim["horizontal"]->setFrameShadow(QFrame::Sunken);
    _delim["horizontal"]->setFrameShape(QFrame::HLine);
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
    _layout->addWidget(_labelPageName.get(), 0, 4, 3, 10);
    _layout->addWidget(_delim["horizontal"].get(), 3, 0, 1, WIDTH / 20 + 1);
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
    QObject::connect(_signButton.get(), SIGNAL(clicked()), this, SLOT(signIn()));
}

void Client::GUI::LoginPage::changeWidth(int width)
{
    this->setFixedSize(width, 100);
}

void Client::GUI::LoginPage::changeUsername(QString username)
{
    this->_username = username.toStdString();
}

void Client::GUI::LoginPage::signIn()
{
    emit changePage(CONTACTS);
}

#include "moc_LoginPage.cpp"
