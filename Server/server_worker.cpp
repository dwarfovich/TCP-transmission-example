#include "server_worker.hpp"

#include <QTcpSocket>
#include <QDataStream>
#include <QDebug>

ServerWorker::ServerWorker(QObject *parent) : QObject { parent }, socket { new QTcpSocket { this } }
{
    buffer.reserve(bufferLimit);

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
    stream.startTransaction();
    uint8_t size = 0;
    stream >> size;
    QByteArray temp;
    stream >> temp;
    if (stream.commitTransaction()) {
        buffer.push_back(size);
        buffer.push_back(temp);
        parseBuffer();
    } else {
        qDebug() << "Failed to commit transaction" << socket->errorString();
    }
}

void ServerWorker::parseBuffer()
{
    if (buffer.isEmpty()) {
        return;
    }

    while (currentMessasgeIndex < buffer.size()) {
        uint8_t currentMessageSize = buffer[currentMessasgeIndex];
        if (currentMessasgeIndex + currentMessageSize < buffer.size()) {
            auto currentMessage = buffer.sliced(currentMessasgeIndex + 1, currentMessageSize);
            emit messageReceived(currentMessage);
            currentMessasgeIndex = currentMessasgeIndex + 1 + currentMessageSize;
            if (buffer.size() >= bufferLimit) {
                rearrangeBuffer();
            }
        } else {
            break;
        }
    }
}

void ServerWorker::rearrangeBuffer()
{
    if (currentMessasgeIndex < buffer.size()) {
        auto restSize = std::distance(buffer.cbegin() + currentMessasgeIndex, buffer.cend());
        if (restSize < std::distance(buffer.cbegin(), buffer.cbegin() + currentMessasgeIndex)) {
            std::copy(buffer.cbegin() + currentMessasgeIndex, buffer.cend(), buffer.begin());
            buffer.resize(restSize);
        }
    } else {
        buffer.clear();
    }
    currentMessasgeIndex = 0;
}
