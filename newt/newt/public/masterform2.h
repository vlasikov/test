#ifndef MASTERFORM2_H
#define MASTERFORM2_H

#include "udpsocket.h"
#include "form2.h"
#include "formdelay.h"
#include "formstatus.h"
#include "settings.h"
#include "calc.h"
#include <MpksSettings.h>
#include <QObject>
#include <QString>

class MasterForm2 : public QObject
{
    Q_OBJECT
public:
    explicit MasterForm2(QObject *parent = 0);
    ~MasterForm2();

    bool saveUdpSettings();
    bool getSettings(QString fileName);
    bool checkMacAddr();
    void CalcUdpIpPort();
    void printUdpSetting();
    void setUdpIpPorts();

    struct AllUdpSettings *Data, *DataUdp;
    uint nUdp;
    Form2 *f;
    FormDelay *fd;
    FormStatus *fs;
    Settings *s;

private:
    MpksSettings *settingsFile;
    QMap<quint32, MpksChannelNodeSettings> uumpks;
    UdpSocket *pUdp[4];
    QByteArray* ansverUdp[4];
    quint16 calcPort[4];
    QString sCalcIP[4];
    bool checkAnsver;
    bool nodeConnect[4];
    quint16 PortD[4];
    quint16 PortS;
    bool compare[4];
    bool MacOK[4];
    bool SaveOK[4];
    QString status_KU[4];

    void requestUdp();
    bool compareStruct();
    void printMacError();
    void statusCalc();
    void showStatus();
    void copyUdpAnswer();

signals:

public slots:
    void sl_control(QString s);
    void sl_udpAnsver(QByteArray *ba);

};

#endif // MASTERFORM2_H
