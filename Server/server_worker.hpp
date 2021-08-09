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

private: // methods
    void parseBuffer();
    void rearrangeBuffer();

private: // data
    QTcpSocket*     socket;
    QByteArray      buffer;
    const qsizetype bufferLimit             = 20;
    qsizetype       currentMessasgeIndex    = 0;
    uint8_t         currentMessageBytesRead = 0;
    uint8_t         expectedMessageSize     = 0;
};

#endif // SERVERWORKER_HPP
