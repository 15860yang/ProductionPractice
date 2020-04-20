#ifndef REMOTESERVICEUTIL_H
#define REMOTESERVICEUTIL_H

#include <QString>
#include<QTcpServer>
#include<QTcpSocket>
#include<QHostInfo>
#include<QHostAddress>

class RemoteServiceUtil:public QObject
{
    Q_OBJECT

private:
    static RemoteServiceUtil* instant;


public:
    QTcpSocket *socket;
    QTcpServer *server;
    quint16 port;
    QString remoteIp;

    static RemoteServiceUtil* getInstant();

    void connectToRemoteServer(QString remoteIp,quint16 port);
    void createRoom();
    void releaseData();
    void writeData(QString byte);
signals:
    void roomConnected();
    void readRemoteData(QString);
    void roomCreateSuccess(QString);
    void hasSomeOneConnectSuccess();

public slots:
    void roomConnectSuccess();
    void resolveConnection();
    void socketReadData();
};

#endif // REMOTESERVICEUTIL_H
