/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-killian.vallette
** File description:
** PageManager
*/

#ifndef PAGEMANAGER_HPP_
#define PAGEMANAGER_HPP_

#include <QtWidgets>
#include <map>
#include "APage.hpp"
#include <iostream>
#include "LoginPage.hpp"
#include "CallPage.hpp"
#include "ContactPage.hpp"
#include "RegisterPage.hpp"

namespace Client
{
    namespace GUI
    {
        class PageManager : public QStackedWidget
        {
            public:
                PageManager(QWidget *parent, ClientInfos_t &infos);
                ~PageManager();
                void addPage(pageNames name);
                void setCurrentPage(pageNames name, ClientInfos_t);
                APage *getPage(pageNames name);

            private:
                //std::map<std::string, std::function<void(QWidget *parent)> _pages;
                std::map<pageNames, std::unique_ptr<APage>> _pages;
                QWidget *_parent;
                ClientInfos_t _infos;
        };

    }
}

#endif /* !PAGEMANAGER_HPP_ */
