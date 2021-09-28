/*
** EPITECH PROJECT, 2021
** Babel
** File description:
** main
*/

#include "BabelClient.hpp"

int main(int argc, char *argv[])
{
    Client::BabelClient client(argc, argv);

    return client.start();
}