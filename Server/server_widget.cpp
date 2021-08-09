#include "server_widget.hpp"
#include "ui_server_widget.h"
#include "chat_server.hpp"

#include <QDebug>

ServerWidget::ServerWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::ServerWidget), server { new ChatServer { this } }
{
    ui->setupUi(this);

    connect(server, &ChatServer::clientConnected, this, &ServerWidget::onClientConnected);
    connect(server, &ChatServer::clientDisconnected, this, &ServerWidget::onClientDisconnected);
    connect(server, &ChatServer::messageReceived, this, &ServerWidget::onMessageReceived);

    QHostAddress address;
    address.setAddress("192.168.50.11");
    server->listen(address, 44100);
    ui->log->appendPlainText("Starting server: listen on " + address.toString() + ", port "
                             + QString::number(server->serverPort()));
}

ServerWidget::~ServerWidget()
{
    delete ui;
}

void ServerWidget::onClientConnected()
{
    ui->log->appendPlainText("New client connected");
}

void ServerWidget::onClientDisconnected()
{
    ui->log->appendPlainText("Client disconnected");
}

void ServerWidget::onMessageReceived(ServerWorker *worker, const QByteArray &message)
{
    int size = message.size();
    ui->log->appendPlainText("Received message" + QString::number(size) + " bytes:");
    ui->log->appendPlainText(QString::fromUtf8(message));
}
