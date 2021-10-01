/*
** EPITECH PROJECT, 2021
** Babel
** File description:
** ContactPage
*/

#include "ContactPage.hpp"

Client::GUI::ContactPage::ContactPage(Client::ClientInfos infos, QWidget *parent) : APage(infos, parent)
{
    setFixedSize(WIDTH, HEIGHT);
    _contactSelected = "";

    loadPage();
    layoutLoader();
}

// LOARDERS

void Client::GUI::ContactPage::loadPage()
{
    callLoader();
    labelLoader();
    contactLoader();
    delimLoader();
    formLoader();
}

void Client::GUI::ContactPage::formLoader()
{
    _contactSearch = std::make_unique<QLineEdit>();
    _writeMsg = std::make_unique<QLineEdit>();

    _contactSearch->setPlaceholderText("search . . .");
    _writeMsg->setPlaceholderText("write a mesage . . .");
}

void Client::GUI::ContactPage::labelLoader()
{
    _imgLogo = std::make_unique<QImage>(LOGO_PATH);
    _labelLogo = std::make_unique<QLabel>();
    _labelPageName = std::make_unique<QLabel>();
    _labelContactName = std::make_unique<QLabel>();
    _labelContactSelected = std::make_unique<QLabel>();

    _labelLogo->setPixmap(QPixmap::fromImage(*_imgLogo));
    _labelLogo->setToolTip("logo du babel des boss du jeu");
    _labelPageName->setText("Babel :: Contact Page");
    _labelPageName->setStyleSheet("QLabel { color : white; }");
    _labelContactName->setText("Contact list");
}

void Client::GUI::ContactPage::callLoader()
{
    _imgCall = std::make_unique<QPixmap>(CALLON_PATH);
    _call = std::make_unique<QPushButton>();
    _backButton = std::make_unique<QPushButton>("Log Out");

    QIcon icon(*_imgCall);
    QSize iconSize(_imgCall->width(), _imgCall->height());

    _call->setIcon(icon);
    _call->setIconSize(iconSize);
    _call->setToolTip("Appelle le contact sélectionné");
    _call->setFlat(true);
    _call->hide();
}

void Client::GUI::ContactPage::contactLoader()
{
    std::size_t nbContact(5);
    std::string name;

    for (std::size_t i = 0; i != nbContact; i++) {
        name = "Contact " + std::to_string(i);
        _contacts.push_back(std::make_shared<QPushButton>(name.c_str()));
        _contacts[i]->setFlat(true);
        _contacts[i]->setFixedSize({WIDTH / 4, HEIGHT / 15});
    }
}

void Client::GUI::ContactPage::delimLoader()
{
    _delim["horizontal"] = std::make_unique<QFrame>();
    _delim["horizontal2"] = std::make_unique<QFrame>();
    _delim["vertical"] = std::make_unique<QFrame>();

    _delim["horizontal"]->setFrameShadow(QFrame::Sunken);
    _delim["horizontal"]->setFrameShape(QFrame::HLine);
    _delim["horizontal2"]->setFrameShadow(QFrame::Sunken);
    _delim["horizontal2"]->setFrameShape(QFrame::HLine);
    _delim["vertical"]->setFrameShadow(QFrame::Sunken);
    _delim["vertical"]->setFrameShape(QFrame::VLine);
}

void Client::GUI::ContactPage::layoutLoader()
{
    _emptyLabel = std::make_unique<QLabel>();
    _layout = std::make_unique<QGridLayout>();

    for (std::size_t i = 0; i < HEIGHT / 20; i++)
        _layout->addWidget(_emptyLabel.get(), i, 0);
    for (std::size_t i = 0; i < WIDTH / 20; i++)
        _layout->addWidget(_emptyLabel.get(), 0, i);
    _layout->addWidget(_labelLogo.get(), 0, 2, 3, 2);
    _layout->addWidget(_labelPageName.get(), 0, 4, 3, 10);
    _layout->addWidget(_labelContactName.get(), 5, 3, 1, 5);
    _layout->addWidget(_labelContactSelected.get(), 4, 16, 1, 10);
    _layout->addWidget(_call.get(), 4, WIDTH / 20, 3, 1);
    // _layout->addWidget(_delim["horizontal"].get(), 3, 0, 1, WIDTH / 20 + 1);
    _layout->addWidget(_delim["horizontal2"].get(), 7, 16, 1, WIDTH / 20 - 15);
    _layout->addWidget(_delim["vertical"].get(), 4, 15, HEIGHT / 20, 1);
    _layout->addWidget(_contactSearch.get(), 6, 2, 2, 10);
    _layout->addWidget(_writeMsg.get(), 28, 16, 2, WIDTH / 20 - 15);
    _layout->addWidget(_backButton.get(), 0, WIDTH / 20, 2, 2);

    for (std::size_t i = 0; i < _contacts.size(); i++)
        _layout->addWidget(_contacts[i].get(), 8 + i * 2, 2, 3, 10);

    this->setLayout(_layout.get());
    initConnections();
}

// CONEXION -- EVENT HANDLER

void Client::GUI::ContactPage::initConnections()
{
    QObject::connect(_backButton.get(), SIGNAL(clicked()), this, SLOT(logOut()));
    for (auto &contact : _contacts)
        QObject::connect(contact.get(), SIGNAL(clicked()), this, SLOT(contactClicked()));
    QObject::connect(_call.get(), SIGNAL(clicked()), this, SLOT(callClicked()));
}

void Client::GUI::ContactPage::contactClicked()
{
    QPushButton *buttonSender = qobject_cast<QPushButton *>(sender());

    for (auto &contact : _contacts)
        contact->setFlat(true);
    if (_contactSelected == buttonSender->text()) {
        _contactSelected = "";
        _call->hide();
    } else {
        _contactSelected = buttonSender->text();
        buttonSender->setFlat(false);
        _call->show();
    }
    _labelContactSelected->setText(_contactSelected);
}

void Client::GUI::ContactPage::callClicked()
{
    std::cout << "GOTO - call page" << std::endl << std::endl;

    emit changePage(CALL);
}

void Client::GUI::ContactPage::logOut()
{
    std::cout << "GOTO - login page" << std::endl << std::endl;

    _contactSelected = "";
    _username = "";
    _labelContactSelected->setText(_contactSelected);
    _call->hide();

    emit changePage(LOGIN);
}

#include "moc_ContactPage.cpp"
