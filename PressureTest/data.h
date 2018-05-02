#ifndef DATA_H
#define DATA_H

#include <QList>

#define PI 3.14159265                               // число ПИ
#define MPKS_RU(X) QTextCodec::codecForName("KOI8-R")->toUnicode(X).toStdString().c_str()

#define TABLE_V 5
#define TABLE_H 4

void inline initTable(QList< QList<QString> > *table)
{
    for (int i=0; i<TABLE_V; i++){
        table->append( QList<QString>());
    }

    (*table)[0].append(MPKS_RU("через 200с"));
    (*table)[0].append(MPKS_RU("не менее 4.80 кгс/см^2"));
    (*table)[0].append(MPKS_RU("4.85 кгс/см^2"));
    (*table)[0].append(MPKS_RU(""));

    (*table)[1].append(MPKS_RU("через 250с"));
    (*table)[1].append(MPKS_RU("не менее 4.87 кгс/см^2"));
    (*table)[1].append(MPKS_RU("4.86 кгс/см^2"));
    (*table)[1].append(MPKS_RU(""));

    (*table)[2].append(MPKS_RU("через 300с"));
    (*table)[2].append(MPKS_RU("не менее 4.90 кгс/см^2"));
    (*table)[2].append(MPKS_RU("4.99 кгс/см^2"));
    (*table)[2].append(MPKS_RU(""));

    (*table)[3].append(MPKS_RU("изменение P с 3 до 4"));
    (*table)[3].append(MPKS_RU("5<t<10"));
    (*table)[3].append(MPKS_RU("15c"));
    (*table)[3].append(MPKS_RU(""));

    (*table)[4].append(MPKS_RU(""));
    (*table)[4].append(MPKS_RU(""));
    (*table)[4].append(MPKS_RU("Общий результат"));
    (*table)[4].append(MPKS_RU(""));
}

#endif // DATA_H
