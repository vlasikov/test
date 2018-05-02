#include "masterform3.h"

MasterForm3::MasterForm3(QObject *parent) :
    QObject(parent)
{
    checkAnsver = false;
    s = new Settings;                   // QSettings
    Data = new struct AllUdpSettings;
    s->read(Data);

    Calc::Port_strToInt(PORT_D_BOOT, &portD);
    Calc::Port_strToInt(PORT_S_BOOT, &portS);
    udp = new UdpSocket;
    udp->datagramSize = 50;
    connect(udp, SIGNAL(sg_udpAnsver(QByteArray*)), this, SLOT(sl_udpAnsver(QByteArray*)));
    udp->setStatus(true);
    udp->setUdpSetting(IP_BOOT, IP_SELF, portD, portS);
    udp->requestSettings();

    fd = new FormDelay;         // форма блокирует сигналы от сокета, поэтому дергаем QCore...
    fd->control();
    delete udp;                 // закрываем соединение, время вышло
    delete fd;

    f = new Form3;
    connect(f, SIGNAL(sg_message(QString)), this, SLOT(sl_control(QString)));

    if (checkAnsver)
        printValue(1);
    f->control();
}

void MasterForm3::sl_control(QString s)
{
    if (s == "form3_b1_save")               // нажали кнопку сохранить
    {
//        bootUdpSettings();
    }
}

void MasterForm3::sl_udpAnsver(QByteArray *ba)
{
    if (50 == ba->size())
    {
        S = (struct ansverForForm3 *) ba->data();
    }

    checkAnsver = true;
}


void MasterForm3::printValue(int i)
{
    if (i==0)
    {
//        newtEntrySet(f->e1, qPrintable(Data->KU[0].IP), 0);
//        newtEntrySet(f->e2, qPrintable(Data->KU[0].MASK), 0);
//        newtEntrySet(f->e3, qPrintable(Data->KU[0].IP_ROUTER), 0);

//        newtEntrySet(f->e4, qPrintable(Data->KU[0].PORT[0]), 0);
//        newtEntrySet(f->e5, qPrintable(Data->KU[0].PORT[1]), 0);
//        newtEntrySet(f->e6, qPrintable(Data->KU[0].PORT[2]), 0);
//        newtEntrySet(f->e7, qPrintable(Data->KU[0].PORT[3]), 0);

//        newtEntrySet(f->e8, qPrintable(Data->KU[0].UU_IP[0]), 0);
//        newtEntrySet(f->e9, qPrintable(Data->KU[0].UU_IP[1]), 0);
//        newtEntrySet(f->e10, qPrintable(Data->KU[0].UU_IP[2]), 0);
//        newtEntrySet(f->e11, qPrintable(Data->KU[0].UU_IP[3]), 0);

//        newtEntrySet(f->e12, qPrintable(Data->KU[0].UU_PORT[0]), 0);
//        newtEntrySet(f->e13, qPrintable(Data->KU[0].UU_PORT[1]), 0);
//        newtEntrySet(f->e14, qPrintable(Data->KU[0].UU_PORT[2]), 0);
//        newtEntrySet(f->e15, qPrintable(Data->KU[0].UU_PORT[3]), 0);
    }
    if (i==1)
    {
        QString s;

        Calc::IP_intToStr(S->IP_KU, &s);
        newtEntrySet(f->e1, qPrintable(s), 0);
        Calc::IP_intToStr(S->Mask_KU, &s);
        newtEntrySet(f->e2, qPrintable(s), 0);
        Calc::IP_intToStr(S->IP_Router, &s);
        newtEntrySet(f->e3, qPrintable(s), 0);

        Calc::Port_intToStr(S->Port_KU[0], &s);
        newtEntrySet(f->e4, qPrintable(s), 0);
        Calc::Port_intToStr(S->Port_KU[1], &s);
        newtEntrySet(f->e5, qPrintable(s), 0);
        Calc::Port_intToStr(S->Port_KU[2], &s);
        newtEntrySet(f->e6, qPrintable(s), 0);
        Calc::Port_intToStr(S->Port_KU[3], &s);
        newtEntrySet(f->e7, qPrintable(s), 0);

        Calc::IP_intToStr(S->IP_UU[0], &s);
        newtEntrySet(f->e8, qPrintable(s), 0);
        Calc::IP_intToStr(S->IP_UU[1], &s);
        newtEntrySet(f->e9, qPrintable(s), 0);
        Calc::IP_intToStr(S->IP_UU[2], &s);
        newtEntrySet(f->e10, qPrintable(s), 0);
        Calc::IP_intToStr(S->IP_UU[3], &s);
        newtEntrySet(f->e11, qPrintable(s), 0);

        Calc::Port_intToStr(S->Port_UU[0], &s);
        newtEntrySet(f->e12, qPrintable(s), 0);
        Calc::Port_intToStr(S->Port_UU[1], &s);
        newtEntrySet(f->e13, qPrintable(s), 0);
        Calc::Port_intToStr(S->Port_UU[2], &s);
        newtEntrySet(f->e14, qPrintable(s), 0);
        Calc::Port_intToStr(S->Port_UU[3], &s);
        newtEntrySet(f->e15, qPrintable(s), 0);

        Calc::MAC_intToStr(S->Mac, &s);
        newtEntrySet(f->e16, qPrintable(s), 0);
    }
}

bool MasterForm3::bootUdpSettings()
{
    udp->requestSettings();

    return true;
}
