/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-killian.vallette
** File description:
** BabelClient
*/

#ifndef BABELCLIENT_HPP_
#define BABELCLIENT_HPP_

class IBabelClient
{
    public:
        IBabelClient(int ac, const char **av);
        virtual void start() = 0;

    private:
        //TODO: Network infos(Myip, port, ip server)
        //TODO: Interface Ipage
        //TODO: IPageManager
};

#endif /* !BABELCLIENT_HPP_ */
