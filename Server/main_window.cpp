#include "main_window.hpp"
#include "ui_main_window.h"
#include "server_widget.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), serverWidget { new ServerWidget { this } }
{
    ui->setupUi(this);
    setWindowTitle("Chat server");
    setCentralWidget(serverWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}
