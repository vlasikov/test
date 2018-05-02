#include "settings.h"

Settings::Settings(QObject *parent) :
    QObject(parent)
{
    settings = new QSettings( "../newt/settings.ini", QSettings::IniFormat );
}

void Settings::write(struct AllUdpSettings *s)
{
    for (int i=0; i<4; i++)
    {
        settings->beginGroup( "KU"+QString::number(1+i) );
        settings->setValue( "IP", s->KU[i].IP );
        settings->setValue( "MASK", s->KU[i].MASK);
        settings->setValue( "IP_ROUTER", s->KU[i].IP_ROUTER );
        settings->setValue( "PORT1", s->KU[i].PORT[0] );
        settings->setValue( "PORT2", s->KU[i].PORT[1] );
        settings->setValue( "PORT3", s->KU[i].PORT[2] );
        settings->setValue( "PORT4", s->KU[i].PORT[3] );
        settings->setValue( "UU_IP1", s->KU[i].UU_IP[0] );
        settings->setValue( "UU_IP2", s->KU[i].UU_IP[1] );
        settings->setValue( "UU_IP3", s->KU[i].UU_IP[2] );
        settings->setValue( "UU_IP4", s->KU[i].UU_IP[3] );
        settings->setValue( "UU_PORT1", s->KU[i].UU_PORT[0] );
        settings->setValue( "UU_PORT2", s->KU[i].UU_PORT[1] );
        settings->setValue( "UU_PORT3", s->KU[i].UU_PORT[2] );
        settings->setValue( "UU_PORT4", s->KU[i].UU_PORT[3] );
        settings->setValue( "MAC", s->KU[i].MAC );
        settings->endGroup();
    }
    settings->sync(); //записываем настройки
}

void Settings::read(struct AllUdpSettings *s)
{
    for (int i=0; i<4; i++)
    {
        settings->beginGroup( "KU"+QString::number(1+i) );

        s->KU[i].IP             = settings->value( "IP", "" ).toString();
        s->KU[i].MASK           = settings->value( "MASK", "" ).toString();
        s->KU[i].IP_ROUTER      = settings->value( "IP_ROUTER", "" ).toString();
        s->KU[i].PORT[0]        = settings->value( "PORT1", "" ).toString();
        s->KU[i].PORT[1]        = settings->value( "PORT2", "" ).toString();
        s->KU[i].PORT[2]        = settings->value( "PORT3", "" ).toString();
        s->KU[i].PORT[3]        = settings->value( "PORT4", "" ).toString();
        s->KU[i].UU_IP[0]       = settings->value( "UU_IP1", "" ).toString();
        s->KU[i].UU_IP[1]       = settings->value( "UU_IP2", "" ).toString();
        s->KU[i].UU_IP[2]       = settings->value( "UU_IP3", "" ).toString();
        s->KU[i].UU_IP[3]       = settings->value( "UU_IP4", "" ).toString();
        s->KU[i].UU_PORT[0]     = settings->value( "UU_PORT1", "" ).toString();
        s->KU[i].UU_PORT[1]     = settings->value( "UU_PORT2", "" ).toString();
        s->KU[i].UU_PORT[2]     = settings->value( "UU_PORT3", "" ).toString();
        s->KU[i].UU_PORT[3]     = settings->value( "UU_PORT4", "" ).toString();
        s->KU[i].MAC            = settings->value( "MAC", "" ).toString();

        settings->endGroup();
    }
}
