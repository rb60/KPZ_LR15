#include "filereader.h"
#include <QFile>
#include <QThread>
#include <QTextStream>

FileReader::FileReader(QObject *parent)
    : QObject{parent}
{}

void FileReader::doWork()
{
    QFile file(path);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QTextStream in(&file);

    int count;
    in >> count;
    QList<int> result(count);
    for(int i = 0; i < count && !in.atEnd(); i++)
    {
        in >> result[i];
        QThread::msleep(1000);
    }
    file.close();
    emit resultReady(result);
}
