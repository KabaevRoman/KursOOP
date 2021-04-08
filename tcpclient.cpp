#include "tcpclient.h"

#include <QDebug>

TcpClient::TcpClient(QHostAddress host, quint16 port) :
    QTcpSocket()
{
    connected = false;
    connectToHost(host,port);
    connect((QAbstractSocket*)this,SIGNAL(connected()),
            this,SLOT(connection()));
    connect((QAbstractSocket*)this,SIGNAL(disconnected()),
            this,SLOT(disconnection()));
    connect((QAbstractSocket*)this,SIGNAL(readyRead()),
            this,SLOT(reading()));
}

void TcpClient::connection()
{
    qDebug()<<"connection";
    connected = true;
    //write("***");
}

void TcpClient::disconnection()
{
    connected = false;
    qDebug()<<"disconnection";
}

void TcpClient::reading()
{
    QByteArray msg;
    msg = readAll();
    if (connected)
    {
        qDebug()<<"reading"<<msg;
        emit recieve(msg);
    }
}

void TcpClient::send(QByteArray msg)
{
    if (connected)
    {
        write(msg);
        qDebug()<<"send"<<msg;
    }
}
