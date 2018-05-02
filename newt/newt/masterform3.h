#ifndef MASTERFORM3_H
#define MASTERFORM3_H

#include "udpsocket.h"
#include "form3.h"
#include "formdelay.h"
#include "settings.h"
#include "calc.h"
#include <QObject>
#include <QString>

class MasterForm3 : public QObject
{
    Q_OBJECT
public:
    explicit MasterForm3(QObject *parent = 0);

    struct AllUdpSettings *Data;
    Settings *s;
    UdpSocket *udp;
    Form3 *f;
    FormDelay *fd;
    quint16 portD, portS;

private:
    bool bootUdpSettings();
    void printValue(int i);
    struct ansverForForm3 *S;
    bool checkAnsver;

signals:

public slots:
    void sl_control(QString s);
    void sl_udpAnsver(QByteArray *ba);
};

#endif // MASTERFORM3_H
