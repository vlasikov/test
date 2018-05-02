#ifndef MASTER_H
#define MASTER_H

#include <newt.h>
#include <stdlib.h>
#include "settings.h"
#include "data.h"
#include "udpsocket.h"
#include "form1.h"
//#include "form2.h"
#include "masterform2.h"
#include "masterform3.h"
#include "masterform4.h"
#include "formdelay.h"
#include "formerror.h"
#include <QObject>
#include <QString>
#include <QTextStream>
#include <QList>
#include <QFile>
#include <QEvent>


class Master:public QObject
{
    Q_OBJECT

public:
    Master(QObject *parent = 0);

    Form1 *f1;
//    Form2 *f2;
    MasterForm2 *mf2;
    MasterForm3 *mf3;
    MasterForm4 *mf4;
    FormDelay *formDelay;
    FormError *formError;
    struct AllUdpSettings UdpData;
    Settings *settings;
private:
    newtComponent form, b1, b2, b3, b4, l1, l2, l3, ch1, rb[3], list1, e1;
    int maxColsScreen, maxRowsScreen, maxColsWin, maxRowsWin;
    QList<QString> file_uu_mpks_ini;

    bool readUdpSettings(QString fileName);
    bool checkMacAddr();
    void CalcUdpIpPort();
    bool saveUdpSettings();
    void initUDP();
    void error(QString);
    void calcWinSize();

public slots:
    void sl_control(QString s);
};

#endif // MASTER_H
