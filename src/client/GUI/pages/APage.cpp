/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-killian.vallette
** File description:
** APage
*/

#include "APage.hpp"


Client::GUI::APage::APage(ClientInfos infos, QWidget *parent) : QWidget(parent) ,_infos(infos)
{
}

void Client::GUI::APage::setClientInfos(const ClientInfos &infos)
{
    _infos = infos;
}

#include "moc_APage.cpp"