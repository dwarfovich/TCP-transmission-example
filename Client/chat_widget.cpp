#include "chat_widget.hpp"
#include "ui_chat_widget.h"
#include "chat_client.hpp"

#include <QHostAddress>

ChatWidget::ChatWidget(QWidget *parent) : QWidget(parent), ui(new Ui::ChatWidget), client { new ChatClient { this } }
{
    ui->setupUi(this);

    connect(client, &ChatClient::connected, this, &ChatWidget::onSocketConnected);
    connect(client, &ChatClient::disconnected, this, &ChatWidget::onSocketDisconnected);
    connect(client, &ChatClient::socketError, this, &ChatWidget::onSocketError);
    connect(client, &ChatClient::logMessage, this, &ChatWidget::onLogMessage);
    connect(ui->connectButton, &QPushButton::clicked, this, &ChatWidget::onConnectButtonClicked);
    connect(ui->disconnectButton, &QPushButton::clicked, this, &ChatWidget::onDisconnectButtonClicked);
    connect(ui->sendMessageButton, &QPushButton::clicked, this, &ChatWidget::sendMessage);
}

ChatWidget::~ChatWidget()
{
    delete ui;
}

void ChatWidget::onSocketConnected()
{}

void ChatWidget::onSocketDisconnected()
{}

void ChatWidget::onSocketError(const QString &error)
{
    ui->log->appendPlainText("Socket error: " + error);
}

void ChatWidget::onConnectButtonClicked()
{
    client->connectToServer(QHostAddress { ui->hostAddressEdit->text() }, ui->portSpinBox->value());
}

void ChatWidget::onDisconnectButtonClicked()
{
    client->disconnect();
}

void ChatWidget::sendMessage()
{
    QString    message = ui->messageEdit->toPlainText();
    QByteArray array { message.toUtf8() };
    client->sendMessage(array);
    ui->log->appendPlainText("Sending message: " + message);
}

void ChatWidget::onLogMessage(const QString &message)
{
    ui->log->appendPlainText("Log: " + message);
}
