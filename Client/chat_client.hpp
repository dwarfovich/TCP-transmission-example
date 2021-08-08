#ifndef CHATCLIENT_HPP
#define CHATCLIENT_HPP

#include <QObject>

class QTcpSocket;
class QHostAddress;

class ChatClient : public QObject
{
    Q_OBJECT

public:
    explicit ChatClient(QObject* parent = nullptr);
    ~ChatClient();

    void connectToServer(const QHostAddress& address, quint16 port);
    void disconnect();
    void sendMessage(const QByteArray& message);

signals:
    void connected();
    void disconnected();
    void socketError(const QString& error);

private slots:
    void onConnected();
    void onDisconnected();
    void onReadyRead();

private:
    QTcpSocket* socket;
};

#endif // CHATCLIENT_HPP
