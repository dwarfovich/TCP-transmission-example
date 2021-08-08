#ifndef CHAT_WIDGET_HPP
#define CHAT_WIDGET_HPP

#include <QWidget>

namespace Ui {
class ChatWidget;
}

class ChatClient;

class ChatWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ChatWidget(QWidget* parent = nullptr);
    ~ChatWidget();

private slots:
    void onSocketConnected();
    void onSocketDisconnected();
    void onSocketError(const QString& error);
    void onConnectButtonClicked();
    void onDisconnectButtonClicked();
    void sendMessage();

private:
    Ui::ChatWidget* ui;
    ChatClient*     client;
};

#endif // CHAT_WIDGET_HPP
