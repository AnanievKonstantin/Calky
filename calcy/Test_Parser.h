#ifndef TEST_PARSER_H
#define TEST_PARSER_H
#include <QObject>
#include <QTest>
#include <Parser.h>


class Test_Parser : public QObject
{

    Q_OBJECT

public:
    Test_Parser(){

    }

signals:

public slots:

private slots:
    void toParce_data()
    {
        QTest::addColumn<QString>("Expression");
        QTest::addColumn<bool>("correct");

        QTest::newRow("test 000") <<"1"<<true;
        QTest::newRow("test 001") <<"0"<<true;
        QTest::newRow("test 002") <<"-1"<<true;
        QTest::newRow("test 003") <<"1.0"<<true;
        QTest::newRow("test 004") <<"-1.0"<<true;
        QTest::newRow("test 005") <<"0.0"<<true;
        QTest::newRow("test 006") <<"-0.0"<<true;
        QTest::newRow("test 007") <<"-0"<<true;
        QTest::newRow("test 009") <<"."<<false;
        QTest::newRow("test 0010") <<"/"<<false;
        QTest::newRow("test 0011") <<"*"<<false;
        QTest::newRow("test 0012") <<"+"<<false;
        QTest::newRow("test 0013") <<"-"<<false;
        QTest::newRow("test 0014") <<"ln(2)"<<true;
        QTest::newRow("test 0015") <<"sin(3)"<<true;
        QTest::newRow("test 0016") <<"cos(5)"<<true;
        QTest::newRow("test 0017") <<"tan(10)"<<true;
        QTest::newRow("test 0018") <<"ctan(10)"<<true;
        QTest::newRow("test 0019") <<"log(10)"<<true;

        QTest::newRow("test 0020") <<"asin(3)"<<true;
        QTest::newRow("test 0021") <<"acos(12)"<<true;
        QTest::newRow("test 0022") <<"sign(5)"<<true;
        QTest::newRow("test 0022") <<"sign(-5)"<<true;
        QTest::newRow("test 0023") <<"sign(2.2)"<<true;
        QTest::newRow("test 0024") <<"sign(-2.2)"<<true;
        QTest::newRow("test 0025") <<"mod(-1)"<<true;
        QTest::newRow("test 0026") <<"mod(1)"<<true;
        QTest::newRow("test 0027") <<"mod(2.1)"<<true;
        QTest::newRow("test 0028") <<"mod(0)"<<true;
        QTest::newRow("test 0029") <<"sqrt(2)"<<true;
        QTest::newRow("test 0020") <<"sqrt(4)"<<true;
        QTest::newRow("test 0021") <<"exp(2)"<<true;
        QTest::newRow("test 0022") <<"log(10 - sin(4))^2"<<true;
        QTest::newRow("test 0023") <<"2^3"<<true;
        QTest::newRow("test 0024") <<"^"<<false;
        QTest::newRow("test 0025") <<"2^3"<<true;
        QTest::newRow("test 0026") <<"(2^2^3)"<<true;
        QTest::newRow("test 0027") <<"(sin(3) - tan(3))"<<true;
        QTest::newRow("test 0028") <<"sin() - cos()"<<true;
        QTest::newRow("test 0029") <<"()"<<true;
        QTest::newRow("test 0030") <<"2*(0)"<<true;
        QTest::newRow("test 0031") <<"(4)-(1)"<<true;
        QTest::newRow("test 0031") <<"4-(1)"<<true;
        QTest::newRow("test 0031") <<"(4)-1"<<true;
        QTest::newRow("test 0031") <<"(4-1)"<<true;
        QTest::newRow("test 0031") <<"4(-1)"<<false;
        QTest::newRow("test 0031") <<"(4-)1"<<false;
        QTest::newRow("test 0031") <<"-(4)"<<true;

    }

    void toParce()
    {


        Parser p;

        QFETCH(QString, Expression);
        QFETCH(bool, correct);

        bool check =p.toPars(Expression.toStdString());

        QCOMPARE(check, correct);

    }

    void get_result()
    {
        Parser p;

    }

    void initTestCase(){
        qDebug("Тестирование:");
    }

    void cleanupTestCase(){
        qDebug("Тестирование завершено");
    }

};

#endif // TEST_PARSER_H
