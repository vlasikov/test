#ifndef FORM3_H
#define FORM3_H

#include <newt.h>
#include <stdlib.h>
#include "data.h"
#include <QString>
#include <QObject>
#include <QTextCodec>

class Form3 : public QObject
{
    Q_OBJECT
public:
    explicit Form3(QObject *parent = 0);    
    void control();
    static void form3Callback(newtComponent co, void * data);

    struct callbackInfo cbis[4];
    newtComponent e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16;
    newtComponent   l1, l2, l3, l4, l5, l6, l7, l8, l9, l10,
                    l11, l12, l13, l14, l15, l16, l17, l18, l19, l20, l21,
                         l22, l23, l24, l25;
    newtComponent form3, b1, b2, b3, b4, ch1, rb[4], list1, scroll;
#ifdef noMCBC
    const char * scaleVal;
#else
    char * scaleVal;
#endif
    int maxColsScreen, maxRowsScreen, maxColsWin, maxRowsWin;


signals:
    void sg_message(QString s);
public slots:

};

#endif // FORM3_H
