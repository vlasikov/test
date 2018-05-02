#ifndef MASTERFORM4_H
#define MASTERFORM4_H

#include "udpsocket.h"
#include "form4.h"
#include "formdelay.h"
#include "settings.h"
#include "calc.h"
#include <QObject>
#include <QString>

class MasterForm4 : public QObject
{
    Q_OBJECT
public:
    explicit MasterForm4(QObject *parent = 0);

    struct AllUdpSettings *Data;
    Settings *s;
    UdpSocket *udp;
    Form4 *f;
    FormDelay *fd;
    quint16 portD, portS;

private:
    bool bootUdpSettings();
    void printValue(int i);
    struct ansverForForm4 *S;
    bool checkAnsver;

signals:

public slots:
    void sl_control(QString s);
//    void sl_udpAnsver(QByteArray *ba);
};

#endif // MASTERFORM4_H
