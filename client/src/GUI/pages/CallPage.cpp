/*
** EPITECH PROJECT, 2021
** Babel
** File description:
** CallPage
*/

#include "CallPage.hpp"

Client::GUI::CallPage::CallPage(ClientInfos infos, QWidget *parent) : APage(infos, parent)
{
    setFixedSize(WIDTH, HEIGHT);

    loadPage();
    layoutLoader();

    // this->setObjectName("TOTO");
    // std::cout << "Nom: "<< this->objectName().toStdString() << std::endl;
}

// LOADERS

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

    _soundOff->hide();
    _micOff->hide();
}

void Client::GUI::CallPage::labelLoader()
{
    _imgLogo = std::make_unique<QImage>(LOGO_PATH);
    _imgProfile = std::make_unique<QImage>(PROFILE96_PATH);
    _labelLogo = std::make_unique<QLabel>();
    _labelProfile = std::make_unique<QLabel>();
    _labelPageName = std::make_unique<QLabel>();
    _labelTimer = std::make_unique<QLabel>();

    _labelLogo->setPixmap(QPixmap::fromImage(*_imgLogo));
    _labelProfile->setPixmap(QPixmap::fromImage(*_imgProfile));
    _labelLogo->setToolTip("logo du babel des boss du jeu");
    _labelPageName->setText("Babel :: Call Page");
    _labelTimer->setText("00 : 00");
}

void Client::GUI::CallPage::delimLoader()
{
    _delim["horizontal"] = std::make_unique<QFrame>();

    _delim["horizontal"]->setFrameShape(QFrame::HLine);
    _delim["horizontal"]->setFrameShadow(QFrame::Sunken);
    _delim["horizontal"]->setFrameShape(QFrame::HLine);
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
    _layout->addWidget(_labelPageName.get(), 0, 4, 3, 10);
    _layout->addWidget(_labelProfile.get(), 10, 20, 6, 3);
    _layout->addWidget(_labelTimer.get(), 16, 21, 2, 1);
    _layout->addWidget(_delim["horizontal"].get(), 3, 0, 1, WIDTH / 20 + 1);

    _layout->addWidget(_soundOn.get(), 25, 15, 3, 2);
    _layout->addWidget(_soundOff.get(), 25, 15, 3, 2);
    _layout->addWidget(_micOn.get(), 25, 20, 3, 2);
    _layout->addWidget(_micOff.get(), 25, 20, 3, 2);
    _layout->addWidget(_callOff.get(), 25, 25, 3, 2);

    this->setLayout(_layout.get());
    initConnections();
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

void Client::GUI::CallPage::callOff()
{
    std::cout << "GOTO - contact page" << std::endl << std::endl;

    _timer->stop();
    _timer->start();
    _eltimer->restart();

    emit changePage(CONTACTS);
}

void Client::GUI::CallPage::updateTimer()
{
    qint64 msecs_elapsed = _eltimer->elapsed();
    std::size_t sec((msecs_elapsed / 1000) % 60);
    std::size_t min(((msecs_elapsed / 1000) % 3600) / 60);
    std::size_t hor(((msecs_elapsed / 1000) % 86400) / 3600);
    std::string time(
        (!hor ? "": std::to_string(hor)) +
        ((min < 10) ? "0": "") + std::to_string(min) + " : " +
        ((sec < 10) ? "0" : "") + std::to_string(sec)
        );

    _labelTimer->setText(time.c_str());
}

#include "moc_CallPage.cpp"
