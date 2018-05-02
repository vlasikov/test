#include <QCoreApplication>
#include "master.h"
#include <QTextCodec>

#include "udpsocket.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
#ifdef noMCBC
    QTextCodec* codec = QTextCodec::codecForName("UTF8");
//    QTextCodec::setCodecForTr(codec);
    QTextCodec::setCodecForCStrings(codec);
//    QTextCodec::setCodecForLocale(codec);
#else
#endif

    Master t;

    return a.exec();
}
