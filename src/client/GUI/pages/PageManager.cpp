/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-killian.vallette
** File description:
** PageManager
*/

#include "PageManager.hpp"

using namespace Client::GUI;

PageManager::PageManager(QWidget *parent) : _parent(parent)
{
    this->addPage(LOGIN);
    this->addPage(REGISTER);
    this->addPage(CONTACTS);
    this->addPage(CALL);
    std::cout << "Page manager created" << std::endl;
}

Client::GUI::PageManager::~PageManager()
{
    std::cout << "PageManager détruit" << std::endl;
}

void PageManager::addPage(pageNames name)
{
    switch (name)
    {
        case LOGIN:
            this->_pages.emplace(LOGIN, std::make_unique<LoginPage>(_infos, _parent));
            break;
        case REGISTER:
            this->_pages.emplace(REGISTER, std::make_unique<RegisterPage>(_infos, _parent));
            break;
        case CALL:
            this->_pages.emplace(CALL, std::make_unique<CallPage>(_infos, _parent));
            break;
        case CONTACTS:
            this->_pages.emplace(CONTACTS, std::make_unique<ContactPage>(_infos, _parent));
            break;
        default:
            break;
    }
    this->addWidget(getPage(name));
}

void PageManager::setCurrentPage(pageNames name, ClientInfos info)
{
    APage *page = getPage(name);

    std::cout << "USERNAME page = " << info.username << std::endl;
    page->setClientInfos(info);
    page->onPage();
    this->setCurrentWidget(page);
}

APage *PageManager::getPage(pageNames name)
{
    return _pages.at(name).get();
}
