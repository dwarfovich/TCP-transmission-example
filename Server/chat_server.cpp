#include "chat_server.hpp"
#include "server_worker.hpp"

ChatServer::ChatServer(QObject *parent) : QTcpServer { parent }
{}

void ChatServer::incomingConnection(qintptr socketDescriptor)
{
    // This method will get called every time a client tries to connect.
    // We create an object that will take care of the communication with this client
    auto *worker = new ServerWorker(this);
    // we attempt to bind the worker to the client
    if (!worker->setSocketDescriptor(socketDescriptor)) {
        // if we fail we clean up
        qDebug() << "Cannot set socket descriptor";
        worker->deleteLater();
        return;
    }
    // connect the signals coming from the object that will take care of the
    // communication with this client to the slots in the central server
    connect(
        worker, &ServerWorker::disconnectedFromClient, this, std::bind(&ChatServer::userDisconnected, this, worker));
    connect(worker,
            &ServerWorker::messageReceived,
            this,
            std::bind(&ChatServer::onMessageReceived, this, worker, std::placeholders::_1));
    // connect(worker, &ServerWorker::error, this, std::bind(&ChatServer::userError, this, worker));

    // connect(worker, &ServerWorker::logMessage, this, &ChatServer::logMessage);
    // we append the new worker to a list of all the objects that communicate to a single client
    clients.push_back(worker);
    emit clientConnected();
    // we log the event
    // emit logMessage(QStringLiteral("New client Connected"));
}

void ChatServer::userDisconnected(ServerWorker *sender)
{
    emit clientDisconnected();
}

void ChatServer::onMessageReceived(ServerWorker *sender, const QByteArray &message)
{
    emit messageReceived(sender, message);
}
