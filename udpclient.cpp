#include "udpclient.h"

MyUDP::MyUDP(QObject *parent) :
    QObject(parent)
{
    socketReceiver = new QUdpSocket(this);
    socketReceiver->bind(1337);

    socketSender = new QUdpSocket(this);
    socketSender->bind(1338);

    QByteArray Data;
    Data.append("Hello");
    QHostAddress a;
    a.setAddress("31.131.27.154");
    socketReceiver->writeDatagram(Data, a, 1337);

    connect(socketReceiver, SIGNAL(readyRead()), this, SLOT(reading()));
    connect(socketSender, SIGNAL(readyRead()), this, SLOT(handshaker()));
}

void MyUDP::HelloUDP(QString msg)
{
    QByteArray Data;
    Data.append(msg);
    QHostAddress a;
    a.setAddress("31.131.27.154");
   // socketSender->writeDatagram(Data, a, 1338);
    socketSender->writeDatagram(" handshake|Shilza|0", a, 1338);
}

void MyUDP::reading()
{
    buffer.resize(socketReceiver->pendingDatagramSize());
    socketReceiver->readDatagram(buffer.data(), buffer.size());
    emit updating();
}

void MyUDP::handshaker()
{
    sessionKey.resize(socketSender->pendingDatagramSize());
    socketSender->readDatagram(sessionKey.data(), sessionKey.size());
    emit updating();
}
