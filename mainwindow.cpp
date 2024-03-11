#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    for(int i = 0; i < WORKERS_COUNT; i++)
    {
        readers[i] = new FileReader;
        readers[i]->path = ":/files/AI" + QString::number(i + 1) + ".txt";
        connect(this, &MainWindow::doWork, readers[i], &FileReader::doWork);
        connect(readers[i], &FileReader::resultReady, this, &MainWindow::addList);
        connect(&threads[i], &QThread::finished, readers[i], &QObject::deleteLater);
        readers[i]->moveToThread(&threads[i]);
        threads[i].start();
    }
    connect(ui->doWorkButton, &QPushButton::clicked, this, &MainWindow::runThreads);

}

MainWindow::~MainWindow()
{
    for(int i = 0; i < WORKERS_COUNT; i++)
    {
        threads[i].exit();
    }
    for(int i = 0; i < WORKERS_COUNT; i++)
    {
        threads[i].wait();
    }
    delete ui;
}

void MainWindow::runThreads()
{
    emit doWork();
}

void MainWindow::addList(QList<int> list)
{
    ui->textEdit->setPlainText(ui->textEdit->toPlainText() + "\n");
    for(int i = 0; i < list.size(); i++)
    {
        ui->textEdit->setPlainText(ui->textEdit->toPlainText() + QString::number(list[i]) + "\n");
    }
}
