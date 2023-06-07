#include "mytcpserver-ex.h"

MyTcpServer::MyTcpServer(QObject *parent) : QObject(parent)
{
    mTcpServer = new QTcpServer(this);
    connect(mTcpServer, &QTcpServer::newConnection, this, &MyTcpServer::slotNewConnection);

    if (!mTcpServer->listen(QHostAddress::Any, 33333)) {
        qDebug() << "Server is not started";
    } else {
        qDebug() << "Server is started";
    }
}

MyTcpServer::~MyTcpServer()
{
    for (QTcpSocket* socket : mTcpSockets) {
        socket->close();
        socket->deleteLater();
    }
    mTcpServer->close();
}

void MyTcpServer::slotNewConnection()
{
    QTcpSocket* newSocket = mTcpServer->nextPendingConnection();
    mTcpSockets.append(newSocket);
    connect(newSocket, &QTcpSocket::readyRead, this, &MyTcpServer::slotServerRead);
    connect(newSocket, &QTcpSocket::disconnected, this, &MyTcpServer::slotClientDisconnected);
}

void MyTcpServer::slotServerRead()
{
    QTcpSocket* socket = static_cast<QTcpSocket*>(sender());
    QByteArray data = socket->readAll();
    QString message(data);
    QStringList messageParts = message.split("&");

    if (messageParts.size() == 3 && messageParts[0] == "sort") {
        int step = messageParts[1].toInt();
        QStringList numbers = messageParts[2].split(" ");
        QStringList result = performHeapSortStep(numbers, step);
        sendStepResult(socket, step, result);
    }
}

void MyTcpServer::sendStepResult(QTcpSocket* socket, int step, const QStringList& numbers)
{
    QByteArray response = QString("Step %1: %2\r\n").arg(step).arg(numbers.join(" ")).toUtf8();
    socket->write(response);
}

QStringList MyTcpServer::performHeapSortStep(const QStringList& numbers, int step)
{
    QStringList sortedNumbers = numbers;
    std::make_heap(sortedNumbers.begin(), sortedNumbers.end());

    for (int i = 0; i < step; ++i) {
        std::pop_heap(sortedNumbers.begin(), sortedNumbers.end() - i);
    }

    std::sort_heap(sortedNumbers.begin(), sortedNumbers.end() - step);

    return sortedNumbers;
}

void MyTcpServer::slotClientDisconnected()
{
    QTcpSocket* socket = static_cast<QTcpSocket*>(sender());
    mTcpSockets.removeOne(socket);
    socket->close();
    socket->deleteLater();
}
