#ifndef FORMDELAY_H
#define FORMDELAY_H

#include <newt.h>
#include <stdlib.h>
#include <QObject>
#include "udpsocket.h"

class FormDelay : public QObject
{
    Q_OBJECT
public:
    explicit FormDelay(QObject *parent = 0);

    UdpSocket *pUdp;
    uint nUdp;
    void control();
private:
    newtComponent formDelay, l1;
    int maxColsScreen, maxRowsScreen, maxColsWin, maxRowsWin;
    int counter, counter2;

    void spinner();


signals:

public slots:

};

#endif // FORMDELAY_H
