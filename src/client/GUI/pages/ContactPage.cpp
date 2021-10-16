/*
** EPITECH PROJECT, 2021
** Babel
** File description:
** ContactPage
*/

#include "ContactPage.hpp"

Client::GUI::ContactPage::ContactPage(Client::ClientInfos_t infos, QWidget *parent) : APage(infos, parent)
{
    setFixedSize(WIDTH, HEIGHT);
    _contactSelected = "";
    _cid = 0;

    QObject::connect(parent, SIGNAL(contactAddSuccess(ClientInfos_t)),
        this, SLOT(validAddContact(ClientInfos_t)));
    QObject::connect(parent, SIGNAL(contactAddFailed(ClientInfos_t)),
        this, SLOT(wrongAddContact(ClientInfos_t)));
    QObject::connect(parent, SIGNAL(incomingCall(ClientInfos_t)),
        this, SLOT(handleIncomingCall(ClientInfos_t)));
    QObject::connect(parent, SIGNAL(contactList(ClientInfos_t)),
        this, SLOT(fillContactList(ClientInfos_t)));
    QObject::connect(parent, SIGNAL(invitationContactReceived(ClientInfos_t)),
        this, SLOT(invitationReceived(ClientInfos_t)));
    QObject::connect(parent, SIGNAL(receivedMessage(ClientInfos_t)),
        this, SLOT(messageReceived(ClientInfos_t)));

    loadPage();
    layoutLoader();
}

void Client::GUI::ContactPage::onPage()
{
    std::cout << "CONTACTPAGE = " << _infos << std::endl;
    _labelContactName->setText(_infos.username.c_str());
    emit checkCommand(_infos, Easkcontactlist);
    if (_timer->isActive())
        _timer->stop();
    _timer->start();
}

// LOARDERS

void Client::GUI::ContactPage::loadPage()
{
    callLoader();
    labelLoader();
    contactLoader();
    delimLoader();
    formLoader();
    timerLoader();
}

void Client::GUI::ContactPage::timerLoader()
{
    _timer = std::make_unique<QTimer>();

    _timer->setInterval(1000);
}

void Client::GUI::ContactPage::formLoader()
{
    _contactSearch = std::make_unique<QLineEdit>();
    _writeMsg = std::make_unique<QLineEdit>();

    _contactSearch->setPlaceholderText("search . . .");
    _writeMsg->setPlaceholderText("write a mesage . . .");
    _writeMsg->hide();
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
    _labelPageName->setText("Contact Page");
    _labelPageName->setStyleSheet("QLabel { color : white; font-size: 30px;}");
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
    _addContactBtn = std::make_unique<QPushButton>("Add contact");
    _contactList = std::make_unique<QListWidget>();
    _messageHistory = std::make_unique<QListWidget>();
    _messageHistory->hide();
}

void Client::GUI::ContactPage::delimLoader()
{
    _delim["horizontal"] = std::make_unique<QFrame>();
    _delim["vertical"] = std::make_unique<QFrame>();

    _delim["horizontal"]->setFrameShadow(QFrame::Sunken);
    _delim["horizontal"]->setFrameShape(QFrame::HLine);
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
    _layout->addWidget(_labelPageName.get(), 0, 15, 3, 10);
    _layout->addWidget(_labelContactName.get(), 5, 4, 1, 5);
    _layout->addWidget(_labelContactSelected.get(), 5, 16, 1, 10);
    _layout->addWidget(_call.get(), 5, WIDTH / 20, 3, 1);

    _layout->addWidget(_delim["horizontal"].get(), 8, 16, 1, WIDTH / 20 - 15);
    _layout->addWidget(_delim["vertical"].get(), 5, 15, HEIGHT / 20, 1);

    _layout->addWidget(_contactSearch.get(), 6, 2, 2, 8);
    _layout->addWidget(_addContactBtn.get(), 8, 2);

    _layout->addWidget(_writeMsg.get(), 28, 16, 2, WIDTH / 20 - 15);
    _layout->addWidget(_backButton.get(), 0, WIDTH / 20, 2, 2);

    _layout->addWidget(_contactList.get(), 10, 2, 20, 10);
    _layout->addWidget(_messageHistory.get(), 9, 16, 19, 28);

    this->setLayout(_layout.get());
    initConnections();
}

// CONEXION -- EVENT HANDLER

void Client::GUI::ContactPage::initConnections()
{
    QObject::connect(_contactSearch.get(), SIGNAL(textChanged(QString)), this, SLOT(searchContact(QString)));
    QObject::connect(_writeMsg.get(), SIGNAL(textChanged(QString)), this, SLOT(changeMsg(QString)));
    QObject::connect(_writeMsg.get(), SIGNAL(returnPressed()), this, SLOT(sendMsg()));
    QObject::connect(_backButton.get(), SIGNAL(clicked()), this, SLOT(logOut()));
    QObject::connect(_contactList.get(), SIGNAL(itemClicked(QListWidgetItem *)), SLOT(contactClicked(QListWidgetItem *)));
    QObject::connect(_call.get(), SIGNAL(clicked()), this, SLOT(callClicked()));
    QObject::connect(_addContactBtn.get(), SIGNAL(clicked()), this, SLOT(addContactClicked()));
    QObject::connect(_timer.get(), SIGNAL(timeout()), this, SLOT(updateTimer()));
}

void Client::GUI::ContactPage::updateTimer()
{
    emit checkCommand(_infos, Easkcontactlist);
}

void Client::GUI::ContactPage::addContactClicked()
{
    bool ok;

    QString text = QInputDialog::getText(
        this,
        tr("Add a new contact"),
        tr("Contact name:"),
        QLineEdit::Normal,
        _contactSearch->text(),
        &ok
    );

    if (ok && !text.isEmpty()) {
        ClientInfos_t info = _infos;
        info.username = text.toStdString().c_str();

        emit checkCommand(info, Eaddcontact);
    }
}

void Client::GUI::ContactPage::contactClicked(QListWidgetItem *item)
{
    _writeMsg->setText("");
    if (_contactSelected == item->text()) {
        _contactSelected = "";
        _call->hide();
        _writeMsg->hide();
        _messageHistory->hide();
    } else {
        _contactSelected = item->text();
        _call->show();
        _writeMsg->show();
        _messageHistory->show();
        while (_messageHistory->count() > 0)
            _messageHistory->takeItem(0);
        for (auto &it : _history) {
            if (it.at(2) != _contactSelected.toStdString())
                continue;
            std::string msg;
            for (auto &jt : it)
                msg += jt;
            new QListWidgetItem(tr(msg.c_str()), _messageHistory.get());
        }
    }

    _labelContactSelected->setText(_contactSelected);
    _infos.currentData = _infos.username + _contactSelected.toStdString();
    emit checkCommand(_infos, EaskHistory);
}

void Client::GUI::ContactPage::callClicked()
{
    std::cout << "GOTO - call page" << std::endl << std::endl;

    _infos.userToCall =  _contactSelected.toStdString();
    _infos.callHost = true;
    if (_timer->isActive())
        _timer->stop();
    emit checkCommand(_infos, EcallX);
    emit changePage(CALL, _infos);
}

void Client::GUI::ContactPage::logOut()
{
    std::cout << "GOTO - login page" << std::endl << std::endl;

    _contactSelected = "";
    _username = "";
    _labelContactSelected->setText(_contactSelected);
    _call->hide();
    while (_contactList->count() > 0)
        _contactList->takeItem(0);
    while (_messageHistory->count() > 0)
        _messageHistory->takeItem(0);

    if (_timer->isActive())
        _timer->stop();
    emit checkCommand(_infos, Elogout);
    emit changePage(LOGIN, _infos);
}

void Client::GUI::ContactPage::changeMsg(QString msg)
{
    this->_msg = msg.toStdString();
}

void Client::GUI::ContactPage::sendMsg()
{
    _infos.currentData = _infos.username + _contactSelected.toStdString() + _msg;
    new QListWidgetItem(tr(_infos.currentData.c_str()), _contactList.get());
    _msg.clear();
    _writeMsg->setText("");
    emit checkCommand(_infos, EsendMsg);
}

void Client::GUI::ContactPage::searchContact(QString search)
{
    this->_search = search.toStdString();

    for (int i = 0; i < _contactList->count(); i++)
    {
        if (_contactList->item(i)->text().toStdString().find(_search) != std::string::npos || _search.empty())
            _contactList->item(i)->setHidden(false);
        else
            _contactList->item(i)->setHidden(true);
    }
}

void Client::GUI::ContactPage::validAddContact(ClientInfos_t info)
{
    QMessageBox msg;
    msg.setText("Contact added successfully !");
    msg.exec();
    new QListWidgetItem(tr(info.currentData.c_str()), _contactList.get());
}

void Client::GUI::ContactPage::wrongAddContact(ClientInfos_t info)
{
    (void)info;
    QMessageBox msg;
    msg.setText("Contact not found !");
    msg.exec();
}

void Client::GUI::ContactPage::invitationReceived(ClientInfos_t info)
{
    QMessageBox msg;
    std::string str(info.currentData + " added you to his contacts !");
    msg.setText(str.c_str());
    msg.exec();
    new QListWidgetItem(tr(info.currentData.c_str()), _contactList.get());
}

void Client::GUI::ContactPage::handleIncomingCall(ClientInfos_t info)
{
    std::vector<std::string> data = convertCurrentData(info.currentData, '\n');

    info.userToCall = data[0];
    info.callerIp = data[1];
    info.callerAudioPort = (unsigned short) std::atoi(data[2].c_str());
    _infos = info;

    if (_timer->isActive())
        _timer->stop();
    emit changePage(CALL, info);
}

void Client::GUI::ContactPage::fillContactList(ClientInfos_t info)
{
    std::vector<std::string> contacts = convertCurrentData(info.currentData, '\n');

    while (_contactList->count() > 0)
        _contactList->takeItem(0);
    for (auto &it : contacts)
        new QListWidgetItem(tr(it.c_str()), _contactList.get());
}

void Client::GUI::ContactPage::messageReceived(ClientInfos_t info)
{
    std::vector<std::string> messages = convertCurrentData(info.currentData, '\n');

    if (messages.size() >= 4) {
        _history.push_back(messages);
        std::cout << "message ID " << IDMSG << " from " << SENDER << "to " << RECEIVER << std::endl;
        std::cout << "with content : " << MESSAGE << std::endl;
    }
}

#include "moc_ContactPage.cpp"
