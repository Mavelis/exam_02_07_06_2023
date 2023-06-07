#include "mytcpserver-unittest.h"

void MyTcpServerUnitTest::testPerformHeapSortStep()
{

    QStringList numbers = { "3", "1", "2", "6", "5" };
    int step = 2;


    QStringList expected = { "1", "2", "3", "5", "6" };


    MyTcpServer server;
    QStringList actual = server.performHeapSortStep(numbers, step);


    QCOMPARE(actual, expected);
}

