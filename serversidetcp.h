#ifndef SERVERSIDETCP_H
#define SERVERSIDETCP_H

#include <QObject>
#include<QTcpServer>
#include<QTcpSocket>
#include <QHash>


class ServerSideTcp : public QObject
{
    Q_OBJECT
public:
    explicit ServerSideTcp(QObject *parent = nullptr);

signals:
    void newMessage(const QByteArray &ba);

public slots:
    void sendMessage(const QString &message);          //send message from client

private slots:
    void onNewConnection();   //when connect to the client
    void onReadyRead();    //when read messages from client
    void onNewMessage(const QByteArray &ba);   //when add rx message
    void onClientDisconnected();


private:
    QString getClientKey(const QTcpSocket *client)const;
private:
    QTcpServer MyServer;
    QHash<QString, QTcpSocket*> MyClients;  //list od clients

};

#endif // SERVERSIDETCP_H
