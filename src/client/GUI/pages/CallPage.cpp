/*
** EPITECH PROJECT, 2021
** Babel
** File description:
** CallPage
*/

#include "CallPage.hpp"

Client::GUI::CallPage::CallPage(ClientInfos infos, QWidget *parent) : APage(infos, parent), _callManager(infos.ip)
{
    setFixedSize(WIDTH, HEIGHT);

    QObject::connect(parent, SIGNAL(incomingCall(ClientInfos)),
        this, SLOT(incoming(ClientInfos)));
    QObject::connect(parent, SIGNAL(callRefused(ClientInfos)),
        this, SLOT(callWasRefused(ClientInfos)));

    loadPage();
    layoutLoader();
}

// LOADERS

void Client::GUI::CallPage::onPage()
{
    _timer->stop();
    _timer->start();
    _eltimer->restart();
    _labelTimer->setText("00 : 00");
}

void Client::GUI::CallPage::loadPage()
{
    btnLoader();
    labelLoader();
    delimLoader();
    timerLoader();
}

void Client::GUI::CallPage::timerLoader()
{
    _timer = std::make_unique<QTimer>();
    _eltimer = std::make_unique<QElapsedTimer>();

    _timer->setInterval(1000);

    _timer->start();
    _eltimer->start();
}

void loadOneButton(std::unique_ptr<QPushButton> &btn, std::unique_ptr<QPixmap> &img, std::string path)
{
    img = std::make_unique<QPixmap>(path.c_str());
    btn = std::make_unique<QPushButton>();

    QIcon icon(*img);
    QSize iconSize(img->width(), img->height());

    btn->setIcon(icon);
    btn->setIconSize(iconSize);
    btn->setFlat(true);
}

void Client::GUI::CallPage::btnLoader()
{
    loadOneButton(_callOff, _imgCallOff, CALLOFF_PATH);
    loadOneButton(_soundOn, _imgSoundOn, SOUNDON_PATH);
    loadOneButton(_soundOff, _imgSoundOff, SOUNDOFF_PATH);
    loadOneButton(_micOn, _imgMicOn, MICON_PATH);
    loadOneButton(_micOff, _imgMicOff, MICOFF_PATH);
    loadOneButton(_validate, _imgValidate, VALIDATE_PATH);
    loadOneButton(_refuse, _imgRefuse, REFUSE_PATH);

    _soundOff->hide();
    _micOff->hide();

    _validate->hide();
    _refuse->hide();
}

void Client::GUI::CallPage::labelLoader()
{
    _imgLogo = std::make_unique<QImage>(LOGO_PATH);
    _imgProfile = std::make_unique<QImage>(PROFILE96_PATH);
    _labelLogo = std::make_unique<QLabel>();
    _labelProfile = std::make_unique<QLabel>();
    _labelPageName = std::make_unique<QLabel>();
    _labelTimer = std::make_unique<QLabel>();
    _labelContact = std::make_unique<QLabel>();
    _gif = std::make_unique<QMovie>(LOGOGIF_PATH);
    _labelGif = std::make_unique<QLabel>();

    _labelGif->setMovie(_gif.get());
    _gif->start();
    _labelLogo->setPixmap(QPixmap::fromImage(*_imgLogo));
    _labelProfile->setPixmap(QPixmap::fromImage(*_imgProfile));
    _labelLogo->setToolTip("logo du babel des boss du jeu");
    _labelContact->setText("Someone calls you . . .");
    _labelPageName->setText("Call Page");
    _labelPageName->setStyleSheet("QLabel { color : white; font-size: 30px;}");
    _labelTimer->setText("00 : 00");

    _labelContact->hide();
    _labelGif->hide();
}

void Client::GUI::CallPage::delimLoader()
{
}

void Client::GUI::CallPage::layoutLoader()
{
    _emptyLabel = std::make_unique<QLabel>();
    _layout = std::make_unique<QGridLayout>();

    for (std::size_t i = 0; i < HEIGHT / 20; i++)
        _layout->addWidget(_emptyLabel.get(), i, 0);
    for (std::size_t i = 0; i < WIDTH / 20; i++)
        _layout->addWidget(_emptyLabel.get(), 0, i);
    _layout->addWidget(_labelLogo.get(), 0, 2, 3, 2);
    _layout->addWidget(_labelPageName.get(), 0, 17, 3, 10);

    inCall();
    incomingCall();

    this->setLayout(_layout.get());
    initConnections();
}

void Client::GUI::CallPage::inCall()
{
    _layout->addWidget(_labelProfile.get(), 10, 18, 6, 3);
    _layout->addWidget(_labelTimer.get(), 18, 19, 2, 1);

    _layout->addWidget(_soundOn.get(), 25, 14, 3, 2);
    _layout->addWidget(_soundOff.get(), 25, 14, 3, 2);
    _layout->addWidget(_micOn.get(), 25, 18, 3, 2);
    _layout->addWidget(_micOff.get(), 25, 18, 3, 2);
    _layout->addWidget(_callOff.get(), 25, 23, 3, 2);
}

void Client::GUI::CallPage::incomingCall()
{
    _layout->addWidget(_labelGif.get(), 8, 17, 10, 5);
    _layout->addWidget(_labelContact.get(), 17, 17, 2, 5);

    _layout->addWidget(_validate.get(), 21, 16, 3, 2);
    _layout->addWidget(_refuse.get(), 21, 21, 3, 2);
}

// CONEXION -- EVENT HANDLER

void Client::GUI::CallPage::initConnections()
{
    QObject::connect(_soundOn.get(), SIGNAL(clicked()), this, SLOT(soundOff()));
    QObject::connect(_soundOff.get(), SIGNAL(clicked()), this, SLOT(soundOn()));
    QObject::connect(_micOn.get(), SIGNAL(clicked()), this, SLOT(micOff()));
    QObject::connect(_micOff.get(), SIGNAL(clicked()), this, SLOT(micOn()));
    QObject::connect(_callOff.get(), SIGNAL(clicked()), this, SLOT(callOff()));
    QObject::connect(_timer.get(), SIGNAL(timeout()), this, SLOT(updateTimer()));
    QObject::connect(_refuse.get(), SIGNAL(clicked()), this, SLOT(endCall()));
    QObject::connect(_validate.get(), SIGNAL(clicked()), this, SLOT(callOn()));
}

void Client::GUI::CallPage::soundOff()
{
    _soundOff->show();
    _soundOn->hide();
}

void Client::GUI::CallPage::soundOn()
{
    _soundOn->show();
    _soundOff->hide();
}

void Client::GUI::CallPage::micOff()
{
    _micOff->show();
    _micOn->hide();
}

void Client::GUI::CallPage::micOn()
{
    _micOn->show();
    _micOff->hide();
}

void Client::GUI::CallPage::endCall()
{
    emit checkCommand(_infos, Erefuseincomingcall);
    callOff();
}

void Client::GUI::CallPage::callOff()
{
    std::cout << "GOTO - contact page" << std::endl << std::endl;

    _timer->stop();
    _timer->start();
    _eltimer->restart();

    _soundOn->show();
    _micOn->show();
    _callOff->show();
    _labelProfile->show();
    _labelTimer->show();

    _validate->hide();
    _refuse->hide();
    _labelContact->hide();
    _labelGif->hide();

    emit changePage(CONTACTS, _infos);
}

void Client::GUI::CallPage::callWasRefused(ClientInfos info)
{
    callOff();
}

void Client::GUI::CallPage::callOn()
{
    _timer->stop();
    _timer->start();
    _eltimer->restart();
    _labelTimer->setText("00 : 00");

    _soundOn->show();
    _micOn->show();
    _callOff->show();
    _labelProfile->show();
    _labelTimer->show();

    _validate->hide();
    _refuse->hide();
    _labelContact->hide();
    _labelGif->hide();

    //emit checkCommand(_infos, EcallX);
}

void Client::GUI::CallPage::updateTimer()
{
    qint64 msecs_elapsed = _eltimer->elapsed();
    std::size_t sec((msecs_elapsed / 1000) % 60);
    std::size_t min(((msecs_elapsed / 1000) % 3600) / 60);
    std::size_t hor(((msecs_elapsed / 1000) % 86400) / 3600);
    std::string time(
        (!hor ? "": std::to_string(hor) + " : ") +
        ((min < 10) ? "0": "") + std::to_string(min) + " : " +
        ((sec < 10) ? "0" : "") + std::to_string(sec)
        );

    _labelTimer->setText(time.c_str());
}

void Client::GUI::CallPage::incoming(ClientInfos info)
{
    _labelProfile->hide();
    _labelTimer->hide();
    _soundOn->hide();
    _micOn->hide();
    _callOff->hide();

    _validate->show();
    _refuse->show();
    _labelContact->show();
    _labelGif->show();
}

#include "moc_CallPage.cpp"
