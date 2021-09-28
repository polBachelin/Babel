/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-killian.vallette
** File description:
** MainWindow
*/

#include "MainWindow.hpp"
#include "Loginpage.hpp"
#include "ContactPage.hpp"
#include <QtGui>

Client::GUI::MainWindow::MainWindow()
{
    // this->mainContainer = std::make_unique<LoginPage>(this);
    this->mainContainer = std::make_unique<ContactPage>(this);

    this->setFixedSize({800, 600});
    this->setCentralWidget(this->mainContainer.get());
    this->setWindowIcon(QIcon("./assets/babelLogo.png"));
}
