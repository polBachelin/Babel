/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-killian.vallette
** File description:
** ITcpClient
*/

#ifndef ITCPCLIENT_HPP_
#define ITCPCLIENT_HPP_

class ITcpClient {
    public:
        ITcpClient();
        ~ITcpClient();
        virtual void connectToHost() = 0;
        //virtual void send(packet_t *packet) = 0;

    protected:
    private:
};

#endif /* !ITCPCLIENT_HPP_ */
