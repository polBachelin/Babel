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

namespace Client {
namespace GUI {

class PageManager : public QStackedWidget
{
    public:
        PageManager();
        ~PageManager() = default;
        void addWidget(APage *page, const std::string &name);
        void setCurrentPage(APage *page, const std::string &name);
        void getPage(APage *page, const std::string &name);

    private:
        std::map<APage*, std::string> _pages;

};

}
}

#endif /* !PAGEMANAGER_HPP_ */
