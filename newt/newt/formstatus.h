#ifndef FORMSTATUS_H
#define FORMSTATUS_H

#include <QObject>
#include <newt.h>
#include <stdlib.h>
#include "data.h"
#include <QString>
#include <QTextCodec>

class FormStatus : public QObject
{
    Q_OBJECT
public:
    explicit FormStatus(QObject *parent = 0);

    int maxColsScreen, maxRowsScreen, maxColsWin, maxRowsWin;
    struct callbackInfo cbis[4];

    void control();

    newtComponent form, b1, b2, b3, b4, l1, l2, l3, ch1, rb[3], list1, e1;
private:
signals:
    void sg_message(QString s);

};

#endif // FORMSTATUS_H
