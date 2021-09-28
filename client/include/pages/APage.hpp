/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-killian.vallette
** File description:
** APage
*/

#ifndef APAGE_HPP_
#define APAGE_HPP_

#include <QtWidgets>
#include <memory>

namespace Client {
namespace GUI {

class APage : public QWidget
{
    //Q_OBJECT

    public:
        APage(QWidget *parent = nullptr);
        ~APage() = default;
        virtual void initConnections() = 0;
    protected:
        std::unique_ptr<QGridLayout> layout;
        QWidget *parent;
};

}
}

#endif /* !APAGE_HPP_ */
