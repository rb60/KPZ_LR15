#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include "filereader.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

const int WORKERS_COUNT = 3;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QThread threads[WORKERS_COUNT];
    FileReader* readers[WORKERS_COUNT];
    Ui::MainWindow *ui;
public slots:
    void runThreads();
    void addList(QList<int> list);
signals:
    void doWork();
};
#endif // MAINWINDOW_H
