#include "remoteserviceutil.h"

RemoteServiceUtil * RemoteServiceUtil::instant = new RemoteServiceUtil();

RemoteServiceUtil* RemoteServiceUtil::getInstant(){
    return instant;
}

void RemoteServiceUtil::connectToRemoteServer(QString remoteIp, quint16 port){
    RemoteServiceUtil::remoteIp = remoteIp;
    RemoteServiceUtil::port = port;
    QHostAddress addr(remoteIp);
    socket = new QTcpSocket();
    socket->connectToHost(addr,port);
    connect(socket,SIGNAL(readyRead()),this,SLOT(socketReadData()));
    connect(socket,SIGNAL(connected()),this,SLOT(roomConnectSuccess()));
}

void RemoteServiceUtil::roomConnectSuccess(){
    emit roomConnected();
}

void RemoteServiceUtil::createRoom(){
    server = new QTcpServer(this);
    QString ipStr = nullptr;
    QList<QHostAddress> list = QHostInfo::fromName(QHostInfo::localHostName()).addresses();
    for(int i = 0; i < list.size(); i++){
        if(list[i].protocol() == QAbstractSocket::IPv4Protocol && list[i].toString().startsWith("192")){
            ipStr = list[i].toString();
            break;
        }
    }
    QHostAddress addr(ipStr);
    connect(server,SIGNAL(newConnection()),this,SLOT(resolveConnection()));
    server->listen(addr,12345);
    qDebug()<<"等待连接。。。";
    emit roomCreateSuccess(ipStr.append("#").append("12345"));
}

void RemoteServiceUtil::resolveConnection(){
    socket = server->nextPendingConnection();
    qDebug()<<"连接成功";
    emit hasSomeOneConnectSuccess();
    connect(socket,SIGNAL(readyRead()),this,SLOT(socketReadData()));
}

void RemoteServiceUtil::writeData(QString data){
    qDebug()<<"RemoteServiceUtil writeData data = "<<data;
    socket->write(data.toStdString().c_str());
}

void RemoteServiceUtil::socketReadData(){
    QByteArray data = socket->readAll();
    qDebug()<<"RemoteServiceUtil接收到消息 data = "<<QString(data);
    emit readRemoteData(QString(data));
}

void RemoteServiceUtil::releaseData(){
    if(server != nullptr){
        server->close();
        delete server;
    }
    if(socket != nullptr){
        socket->close();
        delete socket;
    }
    RemoteServiceUtil::remoteIp = "";
    RemoteServiceUtil::port = -1;
}

