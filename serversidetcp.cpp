#include "serversidetcp.h"

ServerSideTcp::ServerSideTcp(QObject *parent)
    : QObject{parent}
{

    //start listening on port


    //notify when a lient is connected to myserver  using signal and slots
    connect(&MyServer ,&QTcpServer::newConnection ,this ,&ServerSideTcp::onNewConnection);

    //connect to the signal
    connect(this,&ServerSideTcp::newMessage ,this ,&ServerSideTcp::onNewMessage);

    if(MyServer.listen(QHostAddress::Any ,45000)){
        qInfo()<<"server start listening now";
    }
}

void ServerSideTcp::sendMessage(const QString &message)
{

    emit newMessage("Server :" + message.toUtf8());


}

void ServerSideTcp::onNewConnection()
{
    //get the client connection
    const auto client =MyServer.nextPendingConnection();
    if(client==nullptr){
        return;
    }
    else
        qInfo()<<"new client conected";

//    //save the client ip and port
//    QString clientKey =getClientKey(client);

    //add new client to my list
    MyClients.insert(this->getClientKey(client), client);


    //when client is disconnected
    //when client send a message we use signal readyread to read it
    connect(client , &QTcpSocket::readyRead ,this ,&ServerSideTcp::onReadyRead);
    connect(client, &QTcpSocket::disconnected, this, &ServerSideTcp::onClientDisconnected);


}

void ServerSideTcp::onReadyRead()
{
    //sender >>return the object that emmit this signal >>client object
    const auto client =qobject_cast<QTcpSocket*>(sender());
    if(client==nullptr)
        return;

    const auto message = this->getClientKey(client).toUtf8() + ":" + client->readAll();

    //emit new message signal
    emit newMessage(message);
}

void ServerSideTcp::onNewMessage(const QByteArray &ba)
{
    //loop in the clients list and get messagees
    for(const auto &client : qAsConst(MyClients)) {

    //write the message to the client
    client->write(ba);
    client->flush();

    }
}

void ServerSideTcp::onClientDisconnected()
{
    const auto client = qobject_cast<QTcpSocket*>(sender());

    if(client == nullptr) {
        return;
    }

    MyClients.remove(this->getClientKey(client));
}

QString ServerSideTcp::getClientKey(const QTcpSocket *client)const
{
    int  clientPort=client->peerPort();
    QString  clientAddress=client->peerAddress().toString();
    return clientAddress.append(":").append(QString::number(clientPort));
}
