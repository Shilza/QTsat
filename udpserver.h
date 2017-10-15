#ifndef UDPSERVER_H
#define UDPSERVER_H

#include <thread>
#include <memory>
#include <QtSql/QSql>
#include <QtSql/QSqlQuery>
#include <QVector>
#include <QDateTime>
#include <QUdpSocket>
#include <QStringList>
#include <QCryptographicHash>

class UDPServer : public QObject
{
  Q_OBJECT

  public:
      explicit UDPServer(QObject *parent = 0);

  private:
    class Session;
    QUdpSocket *socket, *systemSocket;
    QVector<std::shared_ptr<Session>> sessions;
    QString check(QByteArray sessionKey);
  signals:
      void isReceived(QByteArray message);
  public slots:
      void sendReceived(QByteArray message);
      void read();
      void handshake();
};

#endif // UDPSERVER_H