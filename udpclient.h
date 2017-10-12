#ifndef UDPCLIENT_H
#define UDPCLIENT_H

#include <QObject>
#include <QUdpSocket>

class MyUDP : public QObject
{
    Q_OBJECT
private:
    QUdpSocket *socketReceiver;
    QUdpSocket *socketSender;
    QHostAddress host;

public:
    explicit MyUDP(QObject *parent = 0);
    void HelloUDP(QString msg);
    QByteArray buffer;
    QByteArray sessionKey;
signals:
     void updating();

private slots:
    void reading();
    void handshaking();
};

#endif // UDPCLIENT_H