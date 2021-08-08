#include "chat_client.hpp"

#include <QTcpSocket>
#include <QDataStream>

ChatClient::ChatClient(QObject *parent) : QObject { parent }, socket { new QTcpSocket { this } }
{
    connect(socket, &QTcpSocket::connected, this, &ChatClient::onConnected);
    connect(socket, &QTcpSocket::connected, this, &ChatClient::connected);
    connect(socket, &QTcpSocket::disconnected, this, &ChatClient::onDisconnected);
    connect(socket, &QTcpSocket::disconnected, this, &ChatClient::disconnected);
    connect(socket, &QTcpSocket::readyRead, this, &ChatClient::onReadyRead);
    connect(socket, &QTcpSocket::errorOccurred, this, [this]() {
        emit socketError(socket->errorString());
    });
    // connect(socket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error), this, &ChatClient::error);
}

ChatClient::~ChatClient()
{
    disconnect();
}

void ChatClient::connectToServer(const QHostAddress &address, quint16 port)
{
    socket->connectToHost(address, port, QIODevice::ReadWrite);
}

void ChatClient::disconnect()
{
    socket->disconnectFromHost();
}

void ChatClient::sendMessage(const QByteArray &message)
{
    QDataStream stream { socket };
    stream << (uint8_t)message.size() << message;
}

void ChatClient::onConnected()
{}

void ChatClient::onDisconnected()
{}

void ChatClient::onReadyRead()
{}
