#ifndef FORM2_H
#define FORM2_H

#include <newt.h>
#include <stdlib.h>
#include "data.h"
#include <QString>
#include <QObject>
#include <QTextCodec>



class Form2:public QObject
{
    Q_OBJECT
public:
    char cbValue;
    Form2(QObject *parent = 0);
    void control();
    void sendSignal();

    newtComponent e1, e2, e3, e4;
    newtComponent   l1, l2, l3, l4, l5, l6, l7, l8, l9, l10,
                    l11, l12, l13, l14, l15, l16, l17, l18, l19, l20, l21,
                         l22, l23, l24, l25, l26, l27, l28, l29;
    newtComponent form2, b1, b2, b3, b4, ch1, rb[3], list1, scroll;
    int maxColsScreen, maxRowsScreen, maxColsWin, maxRowsWin;
#ifdef noMCBC
    const char * scaleVal;
#else
    char * scaleVal;
#endif
    QString IP1, MAC1, IP2, MAC2, IP3, MAC3, IP4, MAC4;

//    Form2 *pForm2;

private:
    void initMAC();
    void calcIP();

signals:
    void sg_message(QString s);
};

static int entryHexFilter(newtComponent entry, void * data, int ch, int cursor)
{

    bool ok;

    if (ch >= NEWT_KEY_EXTRA_BASE)
        return ch;

    if ((ch >= '0' && ch <= '9') || ch == 'a' || ch == 'b' || ch == 'c' || ch == 'd' || ch == 'e' || ch == 'f' || ch == ':')// ||  ch >= NEWT_KEY_EXTRA_BASE)
    {
        QString s, s2="", s3, s4 = "", s5 = "", s6;
        int k;

        s = newtEntryGetValue(entry);

        for (int i=0; i<s.size(); i++)      // оставили только числа 0х в строке
        {
            s3 = s.mid(i, 1);
            k = s3.toUInt(&ok, 16);
            if ( ok )
            {
                s4 += s3;
            }
        }

        for (int i=0; i<s4.size(); i+=2)
        {
            s5 += s4.mid(i,2);
            if (s5.size()<16)
                s5 += ":";
        }

        s6 = s5.mid(0,16);
        newtEntrySet(entry, qPrintable(s6), 1);
        k=0;

        return 0;
    }
    else
    {
        return 0;
    }
}

#endif // FORM2_H
