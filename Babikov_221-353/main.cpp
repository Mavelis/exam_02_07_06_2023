#include <QCoreApplication>
#include <QTest>
#include "mytcpserver.h"
#include "mytcpserver-unittest.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    MyTcpServer server;

    // Run the unit tests
    MyTcpServerUnitTest test;
    int testResult = QTest::qExec(&test, argc, argv);

    // Exit with the appropriate return code based on the test results
    return (testResult == 0) ? a.exec() : testResult;
}
