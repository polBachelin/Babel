/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-killian.vallette
** File description:
** MainWindow
*/

#include "MainWindow.hpp"
#include "Loginpage.hpp"

Client::GUI::MainWindow::MainWindow()
{
    this->mainContainer = std::make_unique<LoginPage>(this);

    this->setFixedSize({800, 600});
    this->setCentralWidget(this->mainContainer.get());
}
