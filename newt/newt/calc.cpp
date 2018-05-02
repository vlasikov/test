#include "calc.h"

Calc::Calc(QObject *parent) :
    QObject(parent)
{
}

void Calc::IP_strToInt(QString str, quint8 *i)
{
    bool ok;
    int k[4];
    k[0] = 0;
    QString s="";

    k[1] = str.indexOf(".", 0);
    k[2] = str.indexOf(".", k[1]+1);
    k[3] = str.indexOf(".", k[2]+1);


    for (int q=0; q<4; q++)
    {
        if (q==0)
            s = str.mid(k[q], k[q+1]);
        else
            s = str.mid(k[q]+1, k[q+1] - k[q] - 1);

        i[q] = s.toInt(&ok);

        if (!ok)
        {
            for(int z=0; z<4; z++)
            {
                i[z] = 0;
                return;
            }
        }
    }

    return;
}

void Calc::IP_intToStr(quint8 *i_, QString *str_)
{
    *str_ = "";

    for (int i=0; i<4; i++)
    {
        *str_ += QString::number(i_[i]);
        if (i<3)
        {
            *str_ += ".";
        }
    }
}

void Calc::MAC_strToInt(QString str, quint8 *i)
{
    bool ok;
    int k[6];
    k[0] = 0;
    QString s="";

    k[1] = str.indexOf(":", 0);
    k[2] = str.indexOf(":", k[1]+1);
    k[3] = str.indexOf(":", k[2]+1);
    k[4] = str.indexOf(":", k[3]+1);
    k[5] = str.indexOf(":", k[4]+1);


    for (int q=0; q<6; q++)
    {
        if (q==0)
            s = str.mid(k[q], k[q+1]);
        else
            s = str.mid(k[q]+1, k[q+1] - k[q] - 1);

        i[q] = s.toInt(&ok);

        if (!ok)
        {
            for(int z=0; z<6; z++)
            {
                i[z] = 0;
                return;
            }
        }
    }
    return;
}

void Calc::MAC_intToStr(quint8 *i_, QString *str_)
{
    *str_ = "";

    for (int i=0; i<6; i++)
    {
        if(i_[i] <= 9)
        {
            *str_ += "0";
        }
        *str_ += QString::number(i_[i]);
        if (i<5)
        {
            *str_ += ":";
        }
    }
}

void Calc::Port_strToInt(QString str, quint16 *i)
{
    bool ok;
    *i = str.toInt(&ok);
}

void Calc::Port_intToStr(quint16 i_, QString *str_)
{
    *str_ = "";
    *str_ += QString::number(i_);
}

bool Calc::checkMacAddr(QString *mac)
{
    bool ok, out;
    quint8 hex;
    QString sHex;

    out = false;

    sHex = mac->mid(0, 2);
    hex = sHex.toUInt(&ok, 16);
    if (!ok)
    {
//        *mac = "xx:xx:xx:xx:xx:xx";
        return out;
    }

    sHex = mac->mid(3, 2);
    hex = sHex.toUInt(&ok, 16);
    if (!ok)
    {
//        *mac = "xx:xx:xx:xx:xx:xx";
        return out;
    }

    sHex = mac->mid(6, 2);
    hex = sHex.toUInt(&ok, 16);
    if (!ok)
    {
//        *mac = "xx:xx:xx:xx:xx:xx";
        return out;
    }

    sHex = mac->mid(9, 2);
    hex = sHex.toUInt(&ok, 16);
    if (!ok)
    {
//        *mac = "xx:xx:xx:xx:xx:xx";
        return out;
    }

    sHex = mac->mid(12, 2);
    hex = sHex.toUInt(&ok, 16);
    if (!ok)
    {
//        *mac = "xx:xx:xx:xx:xx:xx";
        return out;
    }

    sHex = mac->mid(15, 2);
    hex = sHex.toUInt(&ok, 16);
    if (!ok)
    {
//        *mac = "xx:xx:xx:xx:xx:xx";
        return out;
    }

    out = true;

    return out;
}

void Calc::CalcIpAndPortFromMac(QString sMac, QString *sIp, quint16 *port)
{
    quint8 ip[4], mac[6];
//    quint16 port;

    ip[3] = 0;
    ip[2] = 0;
    ip[1] = 0;
    ip[0] = 0;
    *port = 0;

    *sIp = "";
    for (int i=0; i<4; i++)
    {
        *sIp += QString::number(ip[i]);
        if(i<3)
            *sIp += ".";
    }

    //        if( !Data->node[j].MacOK )
    //            continue;

    MAC_strToInt(sMac, mac);
    ip[3] = mac[5];
    ip[2] = mac[4];
    ip[1] = mac[3];
    ip[0] = 10;
    *port  = mac[2] + 2048;

    *sIp = "";
    for (int i=0; i<4; i++)
    {
        *sIp += QString::number(ip[i]);
        if(i<3)
            *sIp += ".";
    }
}
