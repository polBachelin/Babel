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
#include "structs.hpp"

namespace Client {
namespace GUI {

    enum pageNames
        {
            LOGIN,
            CONTACTS,
            NEXT
        };

class APage : public QWidget
{
    Q_OBJECT

    public:
        APage(ClientInfos infos, QWidget *parent = nullptr);
        ~APage() = default;
        virtual void initConnections() = 0;

    signals:
        void changePage(pageNames name);


    protected:
        std::unique_ptr<QGridLayout> _layout;
        QWidget *_parent;
        ClientInfos _infos;
};

}
}

#endif /* !APAGE_HPP_ */
