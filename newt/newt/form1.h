#ifndef FORM1_H
#define FORM1_H

#include <newt.h>
#include <stdlib.h>
#include "data.h"
//#include "form2.h"
#include <QObject>
#include <QString>

class Form1:public QObject
{
    Q_OBJECT
public:
    Form1(QObject *parent = 0);

    int maxColsScreen, maxRowsScreen, maxColsWin, maxRowsWin;
    struct callbackInfo cbis[4];

    void control();
private:
    newtComponent form, b1, b2, b3, b4, l1, l2, l3, ch1, rb[3], list1, e1;

signals:
    void sg_message(QString s);
};

#endif // FORM1_H
