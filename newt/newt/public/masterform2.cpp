#include "masterform2.h"

MasterForm2::MasterForm2(QObject *parent) :
    QObject(parent)
{
    // ��������� ��������� �� ini �����
    settingsFile = new MpksSettings;
    settingsFile->readSettings(UU_MPKS_INI);
    uumpks = settingsFile->channelNodesMap();

    nUdp = 4;
    s = new Settings;
    Data = new struct AllUdpSettings;
    DataUdp = new struct AllUdpSettings;
    for (int i=0; i<nUdp; i++)
    {
        SaveOK[i] = false;
        ansverUdp[i] = new QByteArray;
    }

    checkMacAddr();
    requestUdp();
    compareStruct();                // ���������� ������ � ����� � ���������� �� ����

    f = new Form2;
    connect(f, SIGNAL(sg_message(QString)), this, SLOT(sl_control(QString)));


    printUdpSetting();              // ������ ��������
    f->control();
}

MasterForm2::~MasterForm2()
{
}

void MasterForm2::requestUdp()
{
    for(uint i=0; i<nUdp; i++)
    {
        nodeConnect[i] = false;
        ansverUdp[i]->clear();
        QString mac = uumpks.value(i+1).mac();

        QString IpCalc;
        quint16 portD;
        Calc::CalcIpAndPortFromMac(mac, &IpCalc, &portD);
        pUdp[i] = new UdpSocket;
        pUdp[i]->datagramSize = ansverSizeforForm2;
        connect(pUdp[i], SIGNAL(sg_udpAnsver(QByteArray*)), this, SLOT(sl_udpAnsver(QByteArray*)));

        if ( Calc::checkMacAddr( &mac ) )
        {
            pUdp[i]->setStatus(true);
            pUdp[i]->setUdpSetting(IpCalc, IP_SELF, portD, 2000 + i*2);
            pUdp[i]->requestSettings();
        }
        else
        {
            nodeConnect[i] = false;
        }
    }

    fd = new FormDelay;             // ����� ��������� ������� �� ������, ������� ������� QCore...
    fd->control();
    delete fd;

    for (uint i=0; i<nUdp; i++)     // ��������� UDP ����������
        delete pUdp[i];
}

void MasterForm2::sl_udpAnsver(QByteArray *ba)
{
    int numberUdp;
    for (numberUdp=0; numberUdp<4; numberUdp++)
    {
        if (QObject::sender() == pUdp[numberUdp])
        {
            nodeConnect[numberUdp] = true;
            break;
        }
    }

    QString IpCalc;
    quint16 portD;
    Calc::CalcIpAndPortFromMac(uumpks.value(numberUdp+1).mac(), &IpCalc, &portD);

    // ��������� �� ���� ����� ������
    if ( (ansverSizeforForm2 == ba->size()) && (pUdp[numberUdp]->portKU == portD) && (pUdp[numberUdp]->hostKU == QHostAddress(IpCalc)) )
    {
        ansverUdp[numberUdp]->resize(ba->size());
        memmove(ansverUdp[numberUdp]->data(), ba->data(), ba->size());
    }
}

void MasterForm2::sl_control(QString s)
{
    if (QObject::sender() == f)                 // ������� �� ����� �������������� MAC �������
    {
        if (s == "form2_b1_save")               // ������ ������ ���������
        {
            saveUdpSettings();
        }
        if (s == "empty")                       //
        {
            newtLabelSetText(f->l22, ( qPrintable("empty") ));
        }
    }
}

bool MasterForm2::saveUdpSettings()
{
    QString mac[4];
    mac[0] = newtEntryGetValue(f->e1);
    mac[1] = newtEntryGetValue(f->e2);
    mac[2] = newtEntryGetValue(f->e3);
    mac[3] = newtEntryGetValue(f->e4);

    for (int i=0; i<4; i++)
    {
        MacOK[i] = Calc::checkMacAddr(&mac[i]);
        uumpks[i+1].setMac(mac[i]);
    }

    requestUdp();
    compareStruct();                                // ���������� ������ � ����� � ���������� �� ����

    //settingsFile->setChannelNodes(uumpks);
    bool save = true;
    for (int i=0; i<4; i++)
    {
        if (!MacOK[i])
        {
            save = false;
            break;
        }
    }
    if (save)
    {
        if (f->cbValue == 'X')                      // ����������� UDP ������ � ��������� (��� ������ �������������)
            copyUdpAnswer();

        for (int i=0; i<4; i++)
        {
            settingsFile->addChannelNode(uumpks[i+1]);
            settingsFile->writeSettings(UU_MPKS_INI);   // ���������
        }
        showStatus();                               // ���������� ���� ���������� ��� �����
    }
    printUdpSetting();                              // ������ ��������

    return true;
}

void MasterForm2::copyUdpAnswer()
{
    struct ansverForForm2 *S;
    QString str;
    for (int i=0; i<4; i++)
    {
        if (ansverUdp[i]->size())
        {
            S = (struct ansverForForm2 *) ansverUdp[i]->data();

            Calc::IP_intToStr(S->IP_KU, &str);
            uumpks[i+1].setIpChannelNode(str);

            Calc::IP_intToStr(S->Mask_KU, &str);
            uumpks[i+1].setMask(str);

            Calc::IP_intToStr(S->IP_Router, &str);
            uumpks[i+1].setIpRouter(str);
        }
    }
}

void MasterForm2::showStatus()
{
    fs = new FormStatus;

    newtListboxAppendEntry(fs->list1, MPKS_RU("��������� ���������"), (void *) 1);
    if (f->cbValue == 'X')
    {
        newtListboxAppendEntry(fs->list1, MPKS_RU("- � �������������� ��������"), (void *) 1);
        for (int i=0; i<4; i++)
        {
            QString s;
            if (ansverUdp[i]->size())
            {
                s = MPKS_RU("��") + QString::number(i+1) + MPKS_RU(" - � �������������� ��������");
                newtListboxAppendEntry(fs->list1, qPrintable(s), (void *) 1);
            }
            else
            {
                s = MPKS_RU("��") + QString::number(i+1) + MPKS_RU(" - ��� ������������� ��������");
                newtListboxAppendEntry(fs->list1, qPrintable(s), (void *) 1);
            }

        }
    }
    else
        newtListboxAppendEntry(fs->list1, MPKS_RU("- ��� ������������� ��������"), (void *) 1);
    fs->control();

    delete fs;
}

bool MasterForm2::compareStruct()
{
    struct ansverForForm2 *S;
    QString str;
    bool contin = false;
    for(uint i=0; i<nUdp; i++)
    {
        compare[i] = false;

        if (ansverUdp[i]->size())
        {
            S = (struct ansverForForm2 *) ansverUdp[i]->data();

            Calc::IP_intToStr(S->IP_KU, &str);
            if (str != uumpks[i+1].ipChannelNode())
                continue;

            Calc::IP_intToStr(S->IP_Router, &str);
            if (str != uumpks[i+1].ipRouter())
                continue;

            Calc::IP_intToStr(S->Mask_KU, &str);
            if (str != uumpks[i+1].mask())
                continue;

            for (int j=0; j<4; j++)
            {
                Calc::IP_intToStr(S->IP_UU[j], &str);
                if (str != uumpks[i+1].channels()[j].ipAbonent())
                {
                    contin = true;
                    continue;
                }
            }
            if (contin)
                continue;

            compare[i] = true;
        }
    }
    return true;
}

void MasterForm2::printUdpSetting()
{
    newtLabelSetText(f->l5, qPrintable (uumpks.value(1).ipChannelNode()));
    newtLabelSetText(f->l10, qPrintable(uumpks.value(2).ipChannelNode()));
    newtLabelSetText(f->l15, qPrintable(uumpks.value(3).ipChannelNode()));
    newtLabelSetText(f->l20, qPrintable(uumpks.value(4).ipChannelNode()));

    newtEntrySet(f->e1, qPrintable(uumpks.value(1).mac()), 0);
    newtEntrySet(f->e2, qPrintable(uumpks.value(2).mac()), 30);
    newtEntrySetCursorPosition(f->e2, 4);
    newtEntrySet(f->e3, qPrintable(uumpks.value(3).mac()), 0);
    newtEntrySet(f->e4, qPrintable(uumpks.value(4).mac()), 0);

    statusCalc();
    newtLabelSetText(f->l22, ( qPrintable(status_KU[0]) ));
    newtLabelSetText(f->l23, ( qPrintable(status_KU[1]) ));
    newtLabelSetText(f->l24, ( qPrintable(status_KU[2]) ));
    newtLabelSetText(f->l25, ( qPrintable(status_KU[3]) ));
}

void MasterForm2::statusCalc()
{
    for (int i=0; i<4; i++)
    {
        status_KU[i] = "";
        if (MacOK[i])
        {
            if (nodeConnect[i])
            {
                status_KU[i] += MPKS_RU("� ����,");
                if (compare[i])
                {
                    status_KU[i] += MPKS_RU(" ��� ��������,");
                }
                else
                {
                    status_KU[i] += MPKS_RU(" ���� ��������,");
                }

            }
            else
            {
                status_KU[i] += MPKS_RU("�� � ����,");
            }
        }
        else
        {
            status_KU[i] = MPKS_RU(" MAC �� ����������,");
        }
    }
}


bool MasterForm2::checkMacAddr()
{
    for (int i=0; i<4; i++)
    {
        QString mac = uumpks[i+1].mac();
        MacOK[i] = Calc::checkMacAddr(&mac);
    }

    return true;
}
