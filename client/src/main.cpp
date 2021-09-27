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

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    LoginPage toto;

    toto.show();
    return app.exec();
}