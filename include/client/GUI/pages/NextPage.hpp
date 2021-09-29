#ifndef DEF_NEXTPAGE
#define DEF_NEXTPAGE

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

class NextPage : public APage
{
    Q_OBJECT

    public:
        NextPage(ClientInfos infos, QWidget *parent = nullptr);
        ~NextPage();

        void initConnections() override;


    public slots:
        void goBack();

    private:
        std::unique_ptr<QFormLayout> _formLayout;
        std::unique_ptr<QPushButton> _backButton;

        std::string username;
};

}
}

#endif