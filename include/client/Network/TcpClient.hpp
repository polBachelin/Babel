/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-killian.vallette
** File description:
** QTcpClient
*/

#ifndef QTCPCLIENT_HPP_
#define QTCPCLIENT_HPP_

#include "ITcpClient.hpp"
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
        class TcpClient : public QObject
        {
            Q_OBJECT

            public:
                TcpClient(const QString hostAddress, int portVal);
                ~TcpClient();

                bool getStatus();
                QAbstractSocket *getSocket();
                void send(const QByteArray);

            public slots:
                void closeConnection();
                void connectTohost();

            signals:
                void statusChanged(bool);
                void dataAvailable(QByteArray qbt);

            private slots:
                void readyForRead();
                void connected();
                void connectionTimeout();

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
