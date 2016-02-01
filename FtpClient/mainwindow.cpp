#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTcpSocket>

const int portNumber = 1488;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    socket = nullptr;

    init();
}

void MainWindow::doConnect()
{
    if(!socket)
    {
        socket = new QTcpSocket(this);

        connect(socket, &QAbstractSocket::connected,
                this, &MainWindow::slotConnected);
        connect(socket, static_cast<void(QTcpSocket::*)
                (QAbstractSocket::SocketError)>(&QAbstractSocket::error),
                this, &MainWindow::slotError);
    }

    qDebug() << "connecting...";

    socket->connectToHost("localhost", portNumber);
}

void MainWindow::slotError(QAbstractSocket::SocketError err)
{
    switch(err)
    {
    case QAbstractSocket::HostNotFoundError :
    {
        qDebug() << "Error: The host was not found.";
        break;
    }
    case QAbstractSocket::RemoteHostClosedError :
    {
        qDebug() << "Error: The remote host is closed.";
        break;
    }
    case QAbstractSocket::ConnectionRefusedError :
    {
        qDebug() << "Error: The connection was refused.";
        break;
    }
    }
}

void MainWindow::slotConnected()
{
    qDebug() << "connected...";
}

void MainWindow::init()
{
    connect(ui->connectButton, &QPushButton::clicked,
            this, &MainWindow::doConnect);
}

MainWindow::~MainWindow()
{
    delete ui;
}
