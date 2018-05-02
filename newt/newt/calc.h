#ifndef CALC_H
#define CALC_H

#include <QObject>
#include <QString>

class Calc : public QObject
{
    Q_OBJECT
public:
    explicit Calc(QObject *parent = 0);

    static void IP_strToInt(QString str, quint8 *i);
    static void IP_intToStr(quint8 *i_, QString *str_);
    static void MAC_strToInt(QString str, quint8 *i);
    static void MAC_intToStr(quint8 *i_, QString *str_);
    static void Port_strToInt(QString str, quint16 *i);
    static void Port_intToStr(quint16 i_, QString *str_);
    static bool checkMacAddr(QString *mac);
    static void CalcIpAndPortFromMac(QString sMac, QString *sIp, quint16 *port);

signals:

public slots:

};

#endif // CALC_H
