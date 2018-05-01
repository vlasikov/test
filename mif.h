#ifndef MIF_H
#define MIF_H

#include <QObject>
#include <QMainWindow>
#include <QString>
#include <QFile>
#include <QDir>
#include <QMessageBox>
#include <cmath>

class MIF : public QObject
{
    Q_OBJECT

public:
    MIF(QObject *parent = 0);
    void create             (int N, int Width, int Depth, QString BinFileName);
    void writeBinData       (int N, int Width, int Depth, QString BinFileName);
    void deleteMifFile      (QString BinFileName);

private:
    QList<QString> mifFileName;
    QList<QFile*> mifFiles;
    QDataStream stream;
};

#endif // MIF_H
