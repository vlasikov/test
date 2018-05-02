#include "masterform4.h"

MasterForm4::MasterForm4(QObject *parent) :
    QObject(parent)
{
    fd = new FormDelay;         // форма блокирует сигналы от сокета, поэтому дергаем QCore...
    fd->control();
    delete fd;

    f = new Form4;
    connect(f, SIGNAL(sg_message(QString)), this, SLOT(sl_control(QString)));

//    if (checkAnsver)
//        printValue(1);
    f->control();
}

void MasterForm4::sl_control(QString s)
{
    if (s == "form4_b1_save")               // нажали кнопку сохранить
    {
//        bootUdpSettings();
    }
}

