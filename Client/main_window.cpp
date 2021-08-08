#include "main_window.hpp"
#include "ui_main_window.h"
#include "chat_widget.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), chatWidget { new ChatWidget { this } }
{
    ui->setupUi(this);
    setWindowTitle("Chat client");
    setCentralWidget(chatWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}
