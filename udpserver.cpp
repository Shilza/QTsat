#include "udpserver.h"

using std::shared_ptr;
class UDPServer::Session{
public:
    unsigned int time;
    QByteArray sessionKey;
    QString nickname;
    QHostAddress IP;

    Session(QString nickname, QHostAddress IP){
        this->nickname = nickname;
        this->IP = IP;
        time=QDateTime::currentDateTime().toTime_t();
   //     sessionKey = QCryptographicHash::hash(nickname., QCryptographicHash::Md5).toHex();
        QSqlQuery query;
        query.exec("SELECT ID FROM users WHERE Nickname='Shilza'");
        QString id;
        while ( query.next() ) {
            id = query.value(0).toString();
        }
        qDebug() << id;
    }
};


UDPServer::UDPServer(QObject *parent) :
    QObject(parent)
{
    sessions.clear();

    socket = new QUdpSocket(this);
    systemSocket = new QUdpSocket(this);

    socket->bind(QHostAddress::Any, 49001);
    systemSocket->bind(QHostAddress::Any, 49003);

    connect(socket, SIGNAL(readyRead()), this, SLOT(read()));
    connect(systemSocket, SIGNAL(readyRead()), this, SLOT(handshake()));
    connect(this, SIGNAL(isReceived()), this, SLOT(sendReceived()));

}

void UDPServer::sendReceived()
{
    QByteArray Data;
    Data.append("Hello");
   // socket->writeDatagram(Data, , 49000);
}

void UDPServer::read()
{
    message.resize(socket->pendingDatagramSize());
    socket->readDatagram(message.data(), message.size());
    emit isReceived();
}

void UDPServer::handshake(){
    QByteArray buffer;
    quint16 port;
    QHostAddress peer;

    buffer.resize(socket->pendingDatagramSize());
    systemSocket->readDatagram(buffer.data(), buffer.size(), &peer, &port);

    QStringList list = QString(buffer).split('|');
    if(list.at(0)!="handshake")
        return;

/*#include <QCoreApplication>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("Tsat");
    db.setUserName("shilza");
    db.setPassword("192.168.39.26");

    if(db.open())
        qDebug() << "Ok\n";
    else
        qDebug() << "((\n";
*/


    sessions.push_back(shared_ptr<Session>(new Session(list.at(1), peer)));
}




