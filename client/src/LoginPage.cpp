#include "Loginpage.hpp"

LoginPage::LoginPage() : QWidget()
{
    setFixedSize(200, 100);

    m_lcd = new QLCDNumber(this);
    m_lcd->setSegmentStyle(QLCDNumber::Flat);
    m_lcd->move(50, 20);

    m_slider = new QSlider(Qt::Horizontal, this);
    m_slider->setRange(200, 600);
    m_slider->setGeometry(10, 60, 150, 20);

    QObject::connect(m_slider, SIGNAL(valueChanged(int)), this, SLOT(changeWidth(int)));
}

void LoginPage::changeWidth(int width)
{
    this->setFixedSize(width, 100);
}

#include "moc_Loginpage.cpp"