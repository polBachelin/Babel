/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-killian.vallette
** File description:
** QTcpClient
*/

#ifndef QTCPCLIENT_HPP_
#define QTCPCLIENT_HPP_

#include "ITcpClient.hpp"
#include "structs.hpp"
#include <iostream>
#include <memory>
#include <QString>
#include <QTcpSocket>
#include <QDataStream>
#include <QTimer>

#define PACKETSIZE 2060

namespace Client
{
    namespace Network
    {
        class TcpClient : public QObject, public ITcpClient
        {
            Q_OBJECT

            public:
                TcpClient(const QString hostAddress, int portVal);
                ~TcpClient();

                bool getStatus() final;
                QAbstractSocket *getSocket();
                void send(const char *data) final;

            public slots:
                void closeConnection() final;
                void connectToHost() final;

            signals:
                void statusChanged(bool);
                void dataAvailable(QByteArray qbt);

            private slots:
                void readyForRead() final;
                void connected() final;
                void connectionTimeout() final;

            private:
                QString _host;
                int _port;
                bool _status;
                quint16 _m_nNextBlockSize;
                QTimer *_timeoutTimer;
                QTcpSocket* _tcpSocket;
        };

    }
}

#endif /* !QTCPCLIENT_HPP_ */
