/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-killian.vallette
** File description:
** MainWindow
*/

#include "MainWindow.hpp"
#include "APage.hpp"

using namespace Client::GUI;

MainWindow::MainWindow() : _pages(this)
{
    this->setFixedSize({WIDTH, HEIGHT});
    setWindowTitle("Babel");
    this->setCentralWidget(&_pages);
    this->setStyleSheet(
        "background-image:url("
        BACKGROUND_PATH
        "); background-position: center;");

    initConnections();
}

MainWindow::~MainWindow()
{
    std::cout << "MainWindow détruit" << std::endl;
}

void MainWindow::changeCurrentPage(pageNames name)
{
    _pages.setCurrentPage(name);
}

void MainWindow::initConnections(void)
{
    QObject::connect(
        _pages.getPage(LOGIN), SIGNAL(changePage(pageNames)),
        this, SLOT(changeCurrentPage(pageNames)));
    QObject::connect(
        _pages.getPage(REGISTER), SIGNAL(changePage(pageNames)),
        this, SLOT(changeCurrentPage(pageNames)));
    QObject::connect(
        _pages.getPage(CALL), SIGNAL(changePage(pageNames)),
        this, SLOT(changeCurrentPage(pageNames)));
    QObject::connect(
        _pages.getPage(CONTACTS), SIGNAL(changePage(pageNames)),
        this, SLOT(changeCurrentPage(pageNames)));
}

#include "moc_MainWindow.cpp"
