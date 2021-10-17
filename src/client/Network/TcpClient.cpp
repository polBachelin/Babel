/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-killian.vallette
** File description:
** QTcpClient
*/

#include "TcpClient.hpp"

using namespace Client::Network;

TcpClient::TcpClient(
    const QString hostAddress,
    int portNumber
        ) : QObject(), _m_nNextBlockSize(0)
{
    _status = false;
    _host = hostAddress;
    _port = portNumber;
    _tcpSocket = new QTcpSocket(this);
    QObject::connect(_tcpSocket, &QTcpSocket::disconnected, this, &TcpClient::closeConnection);
    _timeoutTimer = new QTimer();
    _timeoutTimer->setSingleShot(true);
    QObject::connect(_timeoutTimer, &QTimer::timeout, this, &TcpClient::connectionTimeout);
    connectToHost();
}

TcpClient::~TcpClient()
{
    delete _tcpSocket;
    delete _timeoutTimer;
}

QAbstractSocket *TcpClient::getSocket()
{
    return _tcpSocket;
}

void TcpClient::connectToHost()
{
    _timeoutTimer->start(3000);

    _tcpSocket->connectToHost(_host, _port);
    QObject::connect(_tcpSocket, &QTcpSocket::connected, this, &TcpClient::connected);
    QObject::connect(_tcpSocket, SIGNAL(readyRead()), this, SLOT(readyForRead()));
}

void TcpClient::connectionTimeout()
{
    if(_tcpSocket->state() == QAbstractSocket::ConnectingState)
    {
        _tcpSocket->abort();
        //emit _tcpSocket->error();
    }
}

void TcpClient::connected()
{
    _status = true;
    emit statusChanged(_status);
}

bool TcpClient::getStatus() {return _status;}

void TcpClient::readyForRead()
{
    QByteArray datas = _tcpSocket->read(PACKETSIZE);
    // qDebug() << datas;
    // std::string str(datas.toStdString());
    // std::cout << "received = " << str << std::endl;
    // QString msg(str.c_str());
    // emit dataAvailable(msg);
    emit dataAvailable(datas);

    // QDataStream in(_tcpSocket);

    // for (;;) {
    //     std::cout << "--loop1" << std::endl;
    //     if (!_m_nNextBlockSize) {
    //         if (_tcpSocket->bytesAvailable() < (qint16) sizeof(quint16)) { break; }
    //         in >> _m_nNextBlockSize;
    //     }

    //     else if (_tcpSocket->bytesAvailable() < _m_nNextBlockSize) { break; }

    //     std::cout << "--loop2" << std::endl;
    //     QString str;
    //     in >> str;
    //     if (str == "0") {
    //         str = "Connection closed";
    //         closeConnection();
    //     }
    //     std::cout << str.toStdString() << std::endl;
    //     emit dataAvailable(str);
    //     _m_nNextBlockSize = 0;
    // }
}

void TcpClient::send(const char *data)
{
    QByteArray QBta = QByteArray::fromRawData(data, sizeof(packet_t));
    _tcpSocket->write(QBta);
}

void TcpClient::closeConnection()
{
    _timeoutTimer->stop();

    //qDebug() << _tcpSocket->state();
    QObject::disconnect(_tcpSocket, &QTcpSocket::connected, 0, 0);
    QObject::disconnect(_tcpSocket, &QTcpSocket::readyRead, 0, 0);

    bool shouldEmit = false;
    switch (_tcpSocket->state())
    {
        case 0:
            _tcpSocket->disconnectFromHost();
            shouldEmit = true;
            break;
        case 2:
            _tcpSocket->abort();
            shouldEmit = true;
            break;
        default:
            _tcpSocket->abort();
    }

    if (shouldEmit)
    {
        std::cout << "Client Disconnected" << std::endl;
        _status = false;
        emit statusChanged(_status);
    }
}

#include "moc_TcpClient.cpp"
