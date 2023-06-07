#ifndef MYSERVER_H
#define MYSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QtNetwork>
#include <QByteArray>
#include <QDebug>
#include <QStringList>
#include <algorithm>

class MyTcpServer : public QObject
{
    Q_OBJECT
public:
    explicit MyTcpServer(QObject *parent = nullptr);
    ~MyTcpServer();
    QStringList performHeapSortStep(const QStringList &numbers, int step);

public slots:
    void slotNewConnection();
    void slotClientDisconnected();
    void slotServerRead();

private:
    QTcpServer *mTcpServer;
    QTcpSocket * mTcpSocket;
    int server_status;
    QList<QTcpSocket*> mTcpSockets;

    void sendStepResult(QTcpSocket *socket, int step, const QStringList &numbers);
};

#endif // MYSERVER_H
