#ifndef MYSERVER_UNITTEST_H
#define MYSERVER_UNITTEST_H

#include <QObject>
#include <QTest>
#include "mytcpserver.h"

class MyTcpServerUnitTest : public QObject
{
    Q_OBJECT

private slots:
    void testPerformHeapSortStep();
};

#endif // MYSERVER_UNITTEST_H
