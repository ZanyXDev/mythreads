#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->startButton->setEnabled( false );
    ui->stopButton->setEnabled( false );


    m_worker = new CPUWorker();

    m_worker->moveToThread(&workThread);
    connect(&workThread, &QThread::finished, m_worker, &QObject::deleteLater);

    connect(ui->loadButton, &QPushButton::clicked, m_worker, &CPUWorker::debugSetRom);
    connect(ui->startButton,&QPushButton::clicked, m_worker, &CPUWorker::start  );
    connect(ui->stopButton, &QPushButton::clicked, m_worker, &CPUWorker::stop  );

    connect(m_worker, &CPUWorker::updateScreenTxt, ui->textEdit, &QTextEdit::append);
    connect(m_worker, &CPUWorker::ReadyToWork, this, &MainWindow::enableButton);

    workThread.start();
}

MainWindow::~MainWindow()
{
    workThread.quit();
    while (!workThread.wait());
    delete ui;
}

void MainWindow::enableButton(bool flag)
{
    ui->startButton->setEnabled( flag );
    ui->stopButton->setEnabled( flag );
}

void MainWindow::testSlot()
{
    ui->runningState->toggle();
}
