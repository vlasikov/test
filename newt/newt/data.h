#ifndef DATA_H
#define DATA_H

#include <newt.h>
#include <QString>

#ifdef noMCBC
#define MPKS_RU(X) QTextCodec::codecForName("KOI8-R")->toUnicode(X).toStdString().c_str()
#else
#define MPKS_RU(X) X
#endif

#define UU_MPKS_INI "../../Mpks/uu_mpks.ini" //"../newt/uu_mpks.ini"

#define IP_BOOT "10.0.10.1"
#define IP_SELF "127.0.0.1"
#define MAC_BOOT "01:02:03:04:05:06"
#define PORT_D_BOOT "2048"
#define PORT_S_BOOT "4003"

#define ansverSizeforForm2 44

// echo 'Hello' > /dev/udp/192.168.18.21/1003

struct UdpSettings
{
    bool MacOK;
    bool KU_connect;
    quint8 MAC[6];
    quint8 IP_Calc[4];
    quint16 Port_calc;
    QString sCalcIP;
    QString sCalcPort;
};
//-----------------------------------------------------------------------
#pragma pack(push, 1)
struct ansverForForm2                      // формат сообщения настройки узла МПКС (44 байта)
{
    quint8 IP_KU[4];
    quint8 Mask_KU[4];
    quint8 IP_Router[4];
    quint16 Port_KU[4];
    quint8 IP_UU[4][4];
    quint16 Port_UU[4];
};
#pragma pack(pop)

//struct struct2
//{
//    QString IP;
//    QString MASK;
//    QString IP_ROUTER;
//    QString PORT[4];
//    QString UU_IP[4];
//    QString UU_PORT[4];
//    QString MAC;
//};

//struct forForm2
//{
//    struct2 KU[4];
//};
//-----------------------------------------------------------------------

#pragma pack(push, 1)
struct ansverForForm3                      // формат сообщения настройки узла МПКС (50 байта)
{
    quint8 IP_KU[4];
    quint8 Mask_KU[4];
    quint8 IP_Router[4];
    quint16 Port_KU[4];
    quint8 IP_UU[4][4];
    quint16 Port_UU[4];
    quint8 Mac[6];
};
#pragma pack(pop)

struct St
{
    QString IP;
    QString MASK;
    QString IP_ROUTER;
    QString PORT[4];
    QString UU_IP[4];
    QString UU_PORT[4];
    QString MAC;
};

struct TermSetting
{
    int minColsWin;
    int minRowsWin;
    int maxColsWin;
    int maxRowsWin;
    int maxColsScreen;
    int maxRowsScreen;
};

struct AllUdpSettings
{
    struct TermSetting terminal;
    struct UdpSettings node[4];     // канальные узлы
    struct St KU[4];
};

struct callbackInfo
{
    newtComponent en;
    char * state;
};

void inline dataInit(struct AllUdpSettings *UdpData)
{
    UdpData->terminal.minColsWin = 80;
    UdpData->terminal.minRowsWin = 25;
}

#endif // DATA_H
