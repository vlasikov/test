#ifndef UDPSOCKET_H
#define UDPSOCKET_H

#include "data.h"
#include <QObject>
#include <QTimer>
#include <QUdpSocket>
#include <QString>

class UdpSocket : public QObject
{
    Q_OBJECT
public:
    explicit UdpSocket(QObject *parent = 0);
    ~UdpSocket();

    QUdpSocket *udpSocket;
    QByteArray *datagram;
    QTimer timer;
    QString IpD, IpS;
    quint16 portD, portS;
    int N_node, datagramSize;
    QHostAddress hostKU;
    quint16 portKU;

    void sendDatagramm(QByteArray datagram);
    void setUdpSetting(QString ipD, QString ipS, quint16 _portD, quint16 _portS);
    bool getStatus();
    void setStatus(bool _ok);
    bool getMpksStatus();
    void requestSettings();
    void socketClose();
private:
    bool status;
    bool statusAnsver;
    struct AllUdpSettings *data;

signals:
    void sg_udpAnsver(QByteArray *ba);

//public slots:
//    QByteArray *processPendingDatagrams();

public slots:
    void processPendingDatagrams();

};

#endif // UDPSOCKET_H
