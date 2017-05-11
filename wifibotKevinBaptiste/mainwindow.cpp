#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    client = new TCPClient();
    QString robotConnectionData = client->getRobotIP() + ":" + QString::number(client->getRobotPort());
    ui->robotIPPort->setText(robotConnectionData);

    initSignals();
}

void MainWindow::initSignals()
{
    connect(ui->connectionButton, SIGNAL (released()), this, SLOT (pushAction()));
    connect(this->client, SIGNAL(reportConnection(QString)), this, SLOT(changeConnectionStatus(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::pushAction()
{
    if(isConnected)
    {
        client->disconnectFromBot();
    }
    else
    {
        client->connectToBot();
    }
}

void MainWindow::changeConnectionStatus(QString status)
{
    this->ui->connectionStatus->setText(status);
    isConnected = !isConnected;
    if(!isConnected)
    {
        ui->connectionButton->setText("Connect to bot");
    }
    else
    {
        ui->connectionButton->setText("Disconnect from bot");
    }
}
