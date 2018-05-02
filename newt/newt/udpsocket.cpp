#include "udpsocket.h"
#include <QtNetwork>

UdpSocket::UdpSocket(QObject *parent) :
    QObject(parent)
{
    udpSocket = new QUdpSocket(this);

    datagram = new QByteArray;
    status = false;
    statusAnsver = false;
    datagramSize = 0;
}

UdpSocket::~UdpSocket()
{
    socketClose();
}

void UdpSocket::socketClose()
{
    udpSocket->abort();
}

void UdpSocket::processPendingDatagrams()
{
    while (udpSocket->hasPendingDatagrams())
    {
        int size = (int)udpSocket->pendingDatagramSize();

        QByteArray *b = new QByteArray;

        b->resize(int(udpSocket->pendingDatagramSize()));
        udpSocket->readDatagram(b->data(), b->size(), &hostKU, &portKU);

        datagram->resize(b->size());
        memmove(datagram->data(), b->data(), b->size());

        statusAnsver = true;
        emit sg_udpAnsver(datagram);
    }
}

void UdpSocket::setUdpSetting(QString ipD, QString ipS, quint16 _portD, quint16 _portS)
{
//    data = d;
    IpD = ipD;
    IpS = ipS;
    portD = _portD;
    portS = _portS;

    udpSocket->bind(QHostAddress(ipS), portS);
    connect(udpSocket, SIGNAL(readyRead()), this, SLOT(processPendingDatagrams()));
}

void UdpSocket::sendDatagramm(QByteArray datagram)
{
    udpSocket->writeDatagram(datagram, QHostAddress(IpD), portD);
}

void UdpSocket::setStatus(bool _ok)
{
    status = _ok;
}

bool UdpSocket::getStatus()
{
    return status;
}

bool UdpSocket::getMpksStatus()
{
    return statusAnsver;
}

void UdpSocket::requestSettings()
{
    if (status)
        sendDatagramm(" ");
}
