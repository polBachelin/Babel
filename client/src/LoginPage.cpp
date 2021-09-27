#include "Loginpage.hpp"

LoginPage::LoginPage(QWidget *parent) : QWidget()
{
    setFixedSize(200, 100);

    usernameForm = std::make_unique<QLineEdit>();
    passwordForm = std::make_unique<QLineEdit>();

    layout = std::make_unique<QFormLayout>();
    layout->addRow("Username", usernameForm.get());
    layout->addRow("Password", passwordForm.get());
    this->setLayout(layout.get());

    //m_slider = new QSlider(Qt::Horizontal, this);
    //m_slider->setRange(200, 600);
    //m_slider->setGeometry(10, 60, 150, 20);

    //QObject::connect(m_slider, SIGNAL(valueChanged(int)), this, SLOT(changeWidth(int)));
    // ? (Component qui send le signal, signal type, component qui reçoit le signal, slot fonction)
    QObject::connect(usernameForm.get(), SIGNAL(textChanged(QString)), this, SLOT(changeUsername(QString)));
}

void LoginPage::changeWidth(int width)
{
    this->setFixedSize(width, 100);
}

void LoginPage::changeUsername(QString username)
{
    this->username = username.toStdString();
}

#include "moc_Loginpage.cpp"