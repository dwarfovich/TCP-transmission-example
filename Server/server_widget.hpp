#ifndef SERVER_WIDGET_HPP
#define SERVER_WIDGET_HPP

#include "server_worker.hpp"

#include <QWidget>

namespace Ui {
class ServerWidget;
}

class ChatServer;
class ServerWorker;

class ServerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ServerWidget(QWidget* parent = nullptr);
    ~ServerWidget();

private slots:
    void onClientConnected();
    void onClientDisconnected();
    void onMessageReceived(ServerWorker* worker, const QByteArray& message);

private:
    Ui::ServerWidget* ui;
    ChatServer*       server;
};

#endif // SERVER_WIDGET_HPP
