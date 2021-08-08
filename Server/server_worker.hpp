#ifndef SERVERWORKER_HPP
#define SERVERWORKER_HPP

#include <QObject>

class QTcpSocket;

class ServerWorker : public QObject
{
    Q_OBJECT

public:
    explicit ServerWorker(QObject* parent = nullptr);

    bool setSocketDescriptor(qintptr socketDescriptor);

signals:
    void disconnectedFromClient();
    void messageReceived(const QByteArray& message);

private slots:
    void onReadyRead();

private:
    QTcpSocket* socket;
    uint8_t     currentMessageSize         = 0;
    uint8_t     currentMessageSizeRemained = 0;
};

#endif // SERVERWORKER_HPP
