#ifndef CHATSERVER_HPP
#define CHATSERVER_HPP

#include <QTcpServer>

#include <vector>

class ServerWorker;

class ChatServer : public QTcpServer
{
    Q_OBJECT

public:
    explicit ChatServer(QObject* parent = nullptr);

signals:
    void clientConnected();
    void clientDisconnected();
    void messageReceived(ServerWorker* sender, const QByteArray& message);

protected:
    void incomingConnection(qintptr socketDescriptor) override;

private slots:
    void userDisconnected(ServerWorker* sender);
    void onMessageReceived(ServerWorker* sender, const QByteArray& message);

private:
    std::vector<ServerWorker*> clients;
};

#endif // CHATSERVER_HPP
