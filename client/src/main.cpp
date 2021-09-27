/*
** EPITECH PROJECT, 2021
** Babel
** File description:
** main
*/

#include <iostream>
#include <QtCore>

#include <QtWidgets/QApplication>
#include <QPushButton>
#include "Loginpage.hpp"
#include "MainWindow.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Client::GUI::MainWindow mainWindow;

    mainWindow.show();
    return app.exec();
}