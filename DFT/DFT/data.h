#ifndef DATA_H
#define DATA_H

#include <QList>

#define PI 3.14159265                               // число ПИ
#define MPKS_RU(X) QTextCodec::codecForName("KOI8-R")->toUnicode(X).toStdString().c_str()

#endif // DATA_H
