#ifndef FILEREADER_H
#define FILEREADER_H

#include <QObject>
#include <QString>
#include <QList>

class FileReader : public QObject
{
    Q_OBJECT
public:
    explicit FileReader(QObject *parent = nullptr);
    QString path = "";
public slots:
    void doWork();
signals:
    void resultReady(QList<int> result);
};

#endif // FILEREADER_H
