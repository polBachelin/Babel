#ifndef DEF_MAFENETRE
#define DEF_MAFENETRE

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLCDNumber>
#include <QSlider>
#include <QtCore/QObject>

class LoginPage : public QWidget
{
    Q_OBJECT

    public:
        LoginPage();
        ~LoginPage() = default;

    public slots:
        void changeWidth(int width);

    private:
        QLCDNumber *m_lcd;
        QSlider *m_slider;
};

#endif