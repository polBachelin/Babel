#ifndef DEF_MAFENETRE
#define DEF_MAFENETRE

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <memory>
#include <QLineEdit>
#include <QFormLayout>
#include <QSlider>
#include <QtCore/QObject>
#include "APage.hpp"

namespace Client {
namespace GUI {

class LoginPage : public APage
{
    Q_OBJECT

    public:
        LoginPage(QWidget *parent = nullptr);
        ~LoginPage() = default;

    //public signals:
    //    void changePageSignIn();

    public slots:
        void changeWidth(int width);
        void changeUsername(QString username);
        void initConnections() override;

    private:
        std::unique_ptr<QPushButton> _signButton;
        std::unique_ptr<QLineEdit> _usernameForm;
        std::unique_ptr<QLineEdit> _passwordForm;
        std::unique_ptr<QFormLayout> _formLayout;

        QSlider *m_slider;
        QWidget *parent;
        std::string username;
};

}
}

#endif