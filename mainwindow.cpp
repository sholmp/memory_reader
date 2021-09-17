#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->getPidButton, &QPushButton::clicked, this, &MainWindow::getPidButtonPushed);
    connect(ui->readMemoryButton, &QPushButton::clicked, this, &MainWindow::readMemoryButtonPushed);

    QTimer* timer = new QTimer;
    timer->setInterval(100);

    ui->memoryContentsLcdNumber->setDigitCount(3);
    ui->pidLcdNumber->setDigitCount(7); // cat /proc/sys/kernel/pid_max -> 4194304

    setWindowTitle("Memory Reader");
}

void MainWindow::getPidButtonPushed()
{
    QByteArray buf = ui->processNameLineEdit->text().toLocal8Bit();
    pidUnderObservation = processManager.getProcessId(buf.data());
    ui->pidLcdNumber->display(pidUnderObservation);
}

void MainWindow::readMemoryButtonPushed()
{
    bool ok;
    int address = ui->addressLineEdit->text().toUInt(&ok, 16);
    int readMemory = processManager.readIntegerFromMemory(pidUnderObservation, address);
    if(!ok)
    {
        qDebug() << "not valid hex address";
        readMemory = -1;
    }

    ui->memoryContentsLcdNumber->display(readMemory);
}

MainWindow::~MainWindow()
{
    delete ui;
}

