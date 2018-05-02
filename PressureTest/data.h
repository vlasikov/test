#ifndef DATA_H
#define DATA_H

#include <QList>

#define PI 3.14159265                               // ����� ��
#define MPKS_RU(X) QTextCodec::codecForName("KOI8-R")->toUnicode(X).toStdString().c_str()

#define TABLE_V 5
#define TABLE_H 4

void inline initTable(QList< QList<QString> > *table)
{
    for (int i=0; i<TABLE_V; i++){
        table->append( QList<QString>());
    }

    (*table)[0].append(MPKS_RU("����� 200�"));
    (*table)[0].append(MPKS_RU("�� ����� 4.80 ���/��^2"));
    (*table)[0].append(MPKS_RU("4.85 ���/��^2"));
    (*table)[0].append(MPKS_RU(""));

    (*table)[1].append(MPKS_RU("����� 250�"));
    (*table)[1].append(MPKS_RU("�� ����� 4.87 ���/��^2"));
    (*table)[1].append(MPKS_RU("4.86 ���/��^2"));
    (*table)[1].append(MPKS_RU(""));

    (*table)[2].append(MPKS_RU("����� 300�"));
    (*table)[2].append(MPKS_RU("�� ����� 4.90 ���/��^2"));
    (*table)[2].append(MPKS_RU("4.99 ���/��^2"));
    (*table)[2].append(MPKS_RU(""));

    (*table)[3].append(MPKS_RU("��������� P � 3 �� 4"));
    (*table)[3].append(MPKS_RU("5<t<10"));
    (*table)[3].append(MPKS_RU("15c"));
    (*table)[3].append(MPKS_RU(""));

    (*table)[4].append(MPKS_RU(""));
    (*table)[4].append(MPKS_RU(""));
    (*table)[4].append(MPKS_RU("����� ���������"));
    (*table)[4].append(MPKS_RU(""));
}

#endif // DATA_H
