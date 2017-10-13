#ifndef UDPSERVER_H
#define UDPSERVER_H

#include <QUdpSocket>

class UDPServer : public QObject
{
  Q_OBJECT

  public:
      explicit UDPServer(QObject *parent = 0);

  private:
      QUdpSocket *socket;
      QByteArray buffer;
      QHostAddress peer;
  signals:
      void forSay();
  public slots:
      void SayHello();
      void readyRead();
};

#endif // UDPSERVER_H