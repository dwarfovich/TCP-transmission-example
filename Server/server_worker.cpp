#include "server_worker.hpp"

#include <QTcpSocket>
#include <QDataStream>
#include <QDebug>

ServerWorker::ServerWorker(QObject *parent) : QObject { parent }, socket { new QTcpSocket { this } }
{
    connect(socket, &QTcpSocket::disconnected, this, &ServerWorker::disconnectedFromClient);
    connect(socket, &QTcpSocket::readyRead, this, &ServerWorker::onReadyRead);
}

bool ServerWorker::setSocketDescriptor(qintptr socketDescriptor)
{
    return socket->setSocketDescriptor(socketDescriptor);
}

void ServerWorker::onReadyRead()
{
    QDataStream stream { socket };
    QByteArray  message;
    stream.startTransaction();
    uint8_t size = 0;
    stream >> size;
    stream >> message;
    if (message.size() == size && stream.commitTransaction()) {
        emit messageReceived(message);
    } else {
        stream.rollbackTransaction();
    }
}
