#ifndef DEF_MAFENETRE
#define DEF_MAFENETRE

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <memory>
#include <QLineEdit>
#include <QFormLayout>
#include <QSlider>
#include <QtCore/QObject>

class LoginPage : public QWidget
{
    Q_OBJECT

    public:
        LoginPage(QWidget *parent = nullptr);
        ~LoginPage() = default;

    public slots:
        void changeWidth(int width);
        void changeUsername(QString username);

    private:
        std::unique_ptr<QLineEdit> usernameForm;
        std::unique_ptr<QLineEdit> passwordForm;
        std::unique_ptr<QFormLayout> layout;
        QSlider *m_slider;
        QWidget *parent;
        std::string username;
};

#endif
