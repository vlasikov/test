#include "mif.h"
#include "mainwindow.h"
#include "QDebug"

MIF::MIF(QObject *parent) :
    QObject(parent)
{

}

void MIF::create(int N, int Width, int Depth, QString BinFileName)  // создаем MIF файлы в соответствии с параметрами на форме
{
    deleteMifFile(BinFileName);                 // удаляем старые MIF файлы

    QString path;
    int i;
    i = BinFileName.lastIndexOf("/");                      // ищем путь до .bin файла
    if (i == -1)
        path = (".");
    else
        path = BinFileName.mid(0, i);

    for (int i=0; i<N; i++)                     // печать шапки файлов
    {
        mifFileName.append(path + "/" + "abc"+QString::number(i+1)+".mif");

        mifFiles.append( new QFile(mifFileName.at(i)) );

        if ( mifFiles.at(i)->open(QIODevice::WriteOnly) )
        {
            mifFiles.at(i)->write( qPrintable((QString)"WIDTH = " + QString::number(Width) + ";\n"));
            mifFiles.at(i)->write( qPrintable((QString)"DEPTH = " + QString::number(Depth) + ";\n"));
            mifFiles.at(i)->write( "\n" );
            mifFiles.at(i)->write( "ADDRESS_RADIX = HEX;\n");
            mifFiles.at(i)->write( "DATA_RADIX = HEX;\n");
            mifFiles.at(i)->write( "\n" );
            mifFiles.at(i)->write( "CONTENT_BEGIN\n" );
        }
        else
        {
            QMessageBox msgBox;
            msgBox.setWindowTitle(mifFileName.at(i));
            msgBox.setText(mifFiles.at(i)->errorString());
            msgBox.exec();

            return;
        }
    }

    writeBinData(N, Width, Depth, BinFileName); // печать бинарнах данных в MIF файлы

    for (int i=0; i<N; i++)                     // печать конца файлов
    {
        mifFiles.at(i)->write( "END;\n" );

        mifFiles.at(i)->close();
    }

    QMessageBox msgBox;
    msgBox.setWindowTitle("Save");
    msgBox.setText(trUtf8("Готово"));
    msgBox.exec();
}

void MIF::deleteMifFile(QString BinFileName)
{
    QString path;
    int i;
    i = BinFileName.lastIndexOf("/");                      // ищем путь до .bin файла
    if (i == -1)
        path = (".");
    else
        path = BinFileName.mid(0, i);

    QDir dir(path);

    QStringList lstFiles = dir.entryList(QStringList("*.mif"), QDir::Files);

    foreach (QString entry, lstFiles)                       // удаляем .mif файлы
      {
       QString entryAbsPath = dir.absolutePath() + "/" + entry;
       if ( !(QFile::setPermissions(entryAbsPath, QFile::ReadOwner | QFile::WriteOwner)) )
       {
           QMessageBox msgBox;
           msgBox.setWindowTitle("Warning");
           msgBox.setText("ошибка при удалении .mif");
           msgBox.exec();
       }
       QFile::remove(entryAbsPath);
      }
}

void MIF::writeBinData(int N, int Width, int Depth, QString BinFileName)
{
    QString str;
    quint64 wordSize = Width/8, byteBinN, wordBinN, wordWriteCurrent=0;
    char c[wordSize];

    QFile binFile(BinFileName);
    if(binFile.open(QIODevice::ReadOnly))
    {
        byteBinN = binFile.size();                  // колличество байт в .bin

        wordBinN = byteBinN / wordSize;             // колличество слов в .bin


        stream.setDevice(&binFile);
        stream.setVersion (QDataStream::Qt_4_8) ;
        if(stream.status() != QDataStream::Ok)
        {
            QMessageBox msgBox;
            msgBox.setWindowTitle(BinFileName);
            msgBox.setText(QString::number(stream.status()));
            msgBox.exec();

            return;
        }
        else
        {
            int strMifCurrent=0, fileN = 0;
            while( (wordBinN > wordWriteCurrent) || (N*Depth > wordBinN) )                         // если бинарные слова не кончились
            {                                                                                      // или MIF слов больше чем BIN слов

                if (wordBinN > wordWriteCurrent)                                                    // если бинарные слова не кончились
                {
                    if ( (strMifCurrent>=Depth))  // если слова не помещаются в MIF
                    {
                        QMessageBox msgBox;
                        msgBox.setWindowTitle("Warning");
                        msgBox.setText(trUtf8("Размер исходного файла превышает размер MIF файлов"));
                        msgBox.exec();

                        return;
                    }
                    mifFiles.at(fileN)->write( qPrintable(" " + QString::number(strMifCurrent, 16) + " : ") );   // печать номера слова

                    if ( stream.atEnd() )
                    {
                        QMessageBox msgBox;
                        msgBox.setWindowTitle("Warning");
                        msgBox.setText(trUtf8("Ошибка в чтения .bin"));
                        msgBox.exec();

                        return;
                    }
                    stream.readRawData(c,wordSize);
                    for (quint64 i=0; i<wordSize; i++)                          // печать слова
                    {
                        str = QString::number((quint8)c[i], 16);
                        mifFiles.at(fileN)->write( qPrintable(str) );
                    }
                }
                else if (N*Depth > wordBinN)                                    // если бинарные слова кончились, но MIF не заполнены
                {
                    if ( (strMifCurrent>=Depth))                                // если MIF заполнены
                    {
                        QMessageBox msgBox;
                        msgBox.setWindowTitle("Warning");
                        msgBox.setText(trUtf8("Размер исходного файла недостаточен для заполнения всех MIF файлов"));
                        msgBox.exec();
                        return;
                    }

                    mifFiles.at(fileN)->write( qPrintable(" " + QString::number(strMifCurrent, 16) + " : ") );   // печать номера слова
                    for (quint64 i=0; i<wordSize; i++)                          // печать слова
                    {
                        str = "FF";
                        mifFiles.at(fileN)->write( qPrintable(str) );
                    }
                }
                mifFiles.at(fileN)->write( ";\n" );

                fileN++;                                                    // переключаем номер файла
                if (N<=fileN)
                {
                    fileN = 0;
                    strMifCurrent++;
                }

                wordWriteCurrent++;                                         // колличество обработанных слов
            }
        }
        binFile.close();
    }
    else                                                                    // не смогли открыть файл
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle(BinFileName);
        msgBox.setText(binFile.errorString());
        msgBox.exec();
        return;
    }
}
