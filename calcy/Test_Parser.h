#ifndef TEST_PARSER_H
#define TEST_PARSER_H
#include <QObject>
#include <QTest>
#include <Parser.h>
#include <math.h>

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
        QTest::newRow("test 002a") <<"sqrt(4)"<<true;
        QTest::newRow("test 002b") <<"exp(2)"<<true;
        QTest::newRow("test 002v") <<"log(10-sin(4))^2"<<true;
        QTest::newRow("test 002d") <<"2^3"<<true;
        QTest::newRow("test 002e") <<"^"<<false;
        QTest::newRow("test 002f") <<"2^3"<<true;
        QTest::newRow("test 002g") <<"(2^2^3)"<<true;
        QTest::newRow("Spases") <<"(sin(3)-tan(3))"<<true;
        //QTest::newRow("Empty scope") <<"sin()-cos()"<<false;
        //QTest::newRow("test 0029") <<"()"<<true;

        QTest::newRow("test 0030") <<"2*(0)"<<true;
        QTest::newRow("test 0031") <<"(4)-(1)"<<true;
        QTest::newRow("test 0032") <<"4-(1)"<<true;
        QTest::newRow("test 0033") <<"(4)-1"<<true;
        QTest::newRow("test 0034") <<"(4-1)"<<true;
        QTest::newRow("Ошибка") <<"4(-1)"<<false;
        QTest::newRow("Ошибка") <<"(4-)1"<<false;
        QTest::newRow("test 0037") <<"-(4)"<<true;

        QTest::newRow("Ошибки в командах1") <<"word(1)"<<false;
        QTest::newRow("Ошибки в командах2") <<"dword(3)"<<false;
        QTest::newRow("Ошибки в командах3") <<"byte(3)"<<false;
        QTest::newRow("Ошибки в командах4") <<"int(2)"<<false;
        QTest::newRow("Ошибки в командах5") <<"lag(3)"<<false;
        QTest::newRow("Ошибки в командах6") <<"sit(5)"<<false;
        QTest::newRow("Ошибки в командах7") <<"ason(2)"<<false;
        QTest::newRow("Ошибки в командах8") <<"asit(2)"<<false;
        QTest::newRow("Ошибки в командах9") <<"acot(2)"<<false;
        QTest::newRow("Ошибки в командах10") <<"acit(2)"<<false;


        QTest::newRow("Закрывающая скобка отсутствует") <<"(2+3"<<false;
        QTest::newRow("Отврывающая скобка отсутствует") <<"3+4)"<<false;
        QTest::newRow("Подряд идущие опрерации") <<"-*3-4"<<false;
        QTest::newRow("Отсутствие второго операнда слева") <<"3*"<<false;
        QTest::newRow("Отсутствие второго операнда справа") <<"*3"<<false;
        QTest::newRow("Баланс скобок") <<"((((2+4)*((2-4)^3)*(3-1))))-2*(3)"<<true;
        QTest::newRow("Баланс скобок в тригономитрических функциях") <<"sin(cos(sin(tan(cos(sin(10))))))"<<true;
        QTest::newRow("Баланс скобок в тригономитрических функциях нарушен (В конце на одну скобку меньше)") <<"sin(cos(tan(ctan(asin(acos(10)))))"<<false;





    }

    void toParce()
    {

        Parser p;
        QFETCH(QString, Expression);
        QFETCH(bool, correct);
        bool check =p.toPars(Expression.toStdString());
        QCOMPARE(check, correct);

    }


    void get_result_data()
    {
        QTest::addColumn<QString>("Expression");
        QTest::addColumn<double>("correct");

        QTest::newRow("test 000") <<"1"<<1.0;
        QTest::newRow("test 001") <<"0"<<0.0;
        QTest::newRow("test 002") <<"-1"<<-1.0;
        QTest::newRow("test 003") <<"1.0"<<1.0;
        QTest::newRow("test 004") <<"-1.0"<<-1.0;
        QTest::newRow("test 005") <<"0.0"<<0.0;
        QTest::newRow("test 006") <<"-0.0"<<0.0;
        QTest::newRow("test 007") <<"-0"<<0.0;
        QTest::newRow("test 009") <<"."<<-1.0;
        QTest::newRow("test 0010") <<"/"<<-1.0;
        QTest::newRow("test 0011") <<"*"<<-1.0;
        QTest::newRow("test 0012") <<"+"<<-1.0;
        QTest::newRow("test 0013") <<"-"<<-1.0;
        QTest::newRow("test 0014") <<"ln(2)"<<log(2.0);
        QTest::newRow("test 0015") <<"sin(3)"<<sin(3.0);
        QTest::newRow("test 0016") <<"cos(5)"<<cos(5.0);
        QTest::newRow("test 0017") <<"tan(10)"<<tan(10.0);
        QTest::newRow("test 0018") <<"ctan(10)"<<1/tan(10.0);
        QTest::newRow("test 0019") <<"log(10)"<<log10(10.0);

        QTest::newRow("test 0020") <<"asin(3)"<<asin(3.0);
        QTest::newRow("test 0021") <<"acos(12)"<<acos(12.0);
        QTest::newRow("test 0022") <<"sign(5)"<<-5.0;
        QTest::newRow("test 0022") <<"sign(-5)"<<5.0;
        QTest::newRow("test 0023") <<"sign(2.2)"<<-2.2;
        QTest::newRow("test 0024") <<"sign(-2.2)"<<2.2;
        QTest::newRow("test 0025") <<"mod(-1)"<<1.0;
        QTest::newRow("test 0026") <<"mod(1)"<<1.0;
        QTest::newRow("test 0027") <<"mod(2.1)"<<2.1;
        QTest::newRow("test 0028") <<"mod(0)"<<0.0;
        QTest::newRow("test 0029") <<"sqrt(2)"<<sqrt(2.0);
        QTest::newRow("test 002a") <<"sqrt(4)"<<sqrt(4.0);
        QTest::newRow("test 002b") <<"exp(2)"<<exp(2.0);
        QTest::newRow("test 002c") <<"log(10-sin(4))^2"<<pow(log10(10.0-sin(4.0)),2.0);
        QTest::newRow("test 002d") <<"2^3"<<pow(2.0,3.0);
        QTest::newRow("test 002e") <<"^"<<-1.0;
        QTest::newRow("test 002f") <<"2^(-3)"<<pow(2.0,-3.0);
        QTest::newRow("test 002g") <<"(2^2^3)"<<pow(2.0,pow(2.0,3.0));
        QTest::newRow("trigonametrial") <<"(sin(3)-tan(3))"<<(sin(3.0)-tan(3.0));
        QTest::newRow("Trigonometrial rule") <<"sin(2)^2+cos(2)^2"<<1.0;
        QTest::newRow("test 0029") <<"sqrt(3^2+3^3)"<<sqrt(pow(3,2)+pow(3,3));

        QTest::newRow("test 0030") <<"2*(0)"<<0.0;
        QTest::newRow("test 0031") <<"(4)-(1)"<<3.0;
        QTest::newRow("test 0032") <<"4-(1)"<<3.0;
        QTest::newRow("test 0033") <<"(4)-1"<<3.0;
        QTest::newRow("test 0034") <<"(4-1)"<<3.0;
        QTest::newRow("Ошибка") <<"4(-1)"<<-1.0;
        QTest::newRow("Ошибка") <<"(4-)1"<<-1.0;
        QTest::newRow("test 0037") <<"-(4)"<<-4.0;


        QTest::newRow("Ошибки расчета сложных выражений1") <<"(sin(90)^2)-tan(12)*(6/2)!"<<pow(sin(90.0),2.0)-tan(12.0)*6.0;
        QTest::newRow("Ошибки расчета сложных выражений2") <<"((sin(42)-1)^3)-6*(22-(3*2))"<<pow(sin(42)-1,3)-6*(22-(3*2));
        QTest::newRow("Ошибки расчета сложных выражений3") <<"-(12*(7^2)^(sin(2)))/(-42.12)"<<-(12.0*(pow(pow(7.0,2.0),sin(2.0))))/-42.12;
        QTest::newRow("Ошибки расчета сложных выражений4") <<"2.0+3-4.0+4-4.0+3-2.0+4-2.0+1-4.0+10-123.0+2134-4.0+2-24.0+234-123.0"<<
                                                            2.0+3-4.0+4.0-4.0+3.0-2.0+4.0-2.0+1.0-4.0+10.0-123.0+2134.0-4.0+2.0-24.0+234.0-123.0;
        QTest::newRow("Ошибки расчета сложных выражений5") <<"(2-3)-(1-2)"<<(2.0-3.0)-(1.0-2.0);
        QTest::newRow("Ошибки расчета сложных выражений6") <<"22/7"<<3.142857142857143;
        //QTest::newRow("Ошибки расчета сложных выражений7 очевиден выход за разрядную сетку double") <<"100!"<<93326215443944152681699238856266700490715968264381621468592963895217599993229915608941463976156518286253697920827223758251185210916864000000000000000000000000.0;
        //QTest::newRow("Ошибки расчета сложных выражений8 выкидывает исключение") <<"3333333333"<<3333333333.0;
        QTest::newRow("Ошибки расчета сложных выражений9") <<"0.00000000000001+0.00000000000001"<<0.00000000000002;
    }


    void get_result()
    {
        Parser p;
        QFETCH(QString, Expression);
        QFETCH(double, correct);
        p.toPars(Expression.toStdString());

        QCOMPARE(p.get_result(), correct);
    }

    void is_correct_data()
    {
        QTest::addColumn<QString>("Expression");
        QTest::addColumn<bool>("correct");

        QTest::newRow("test 000") <<""<<true;
        QTest::newRow("test 001") <<"()"<<true;
        QTest::newRow("test 002") <<"("<<false;
        QTest::newRow("test 003") <<")"<<false;
        QTest::newRow("test 004") <<"((1+2)"<<false;
        QTest::newRow("test 005") <<"(1+2))"<<false;
        QTest::newRow("test 006") <<"sin(2"<<false;
        QTest::newRow("test 007") <<"sin3)"<<false;
        QTest::newRow("test 009") <<"(cos))"<<false;
        QTest::newRow("test 0010") <<"()+()+()+()"<<true;
        QTest::newRow("test 0011") <<"(1*2)+(3)-(3+3/2)-(11*2)"<<true;
        QTest::newRow("test 0012") <<"(((((((((())))))))))"<<true;
        QTest::newRow("test 0013") <<"(("<<false;
        QTest::newRow("test 0014") <<"))"<<false;
        QTest::newRow("test 0015") <<")("<<false;
        QTest::newRow("test 0016") <<")()("<<false;
        QTest::newRow("test 0017") <<"tan((10))"<<true;
        QTest::newRow("test 0018") <<"ctan((100-1)-7)"<<true;
        QTest::newRow("test 0019") <<"(1-3*(log(10)))"<<true;
    }

    void is_correct()
    {

        Parser p;
        QFETCH(QString, Expression);
        QFETCH(bool, correct);

        string s = Expression.toStdString();

        bool check = p.is_correct(&s);
        QCOMPARE(check, correct);

    }

    void initTestCase(){
        qDebug("Тестирование:");
    }

    void cleanupTestCase(){
        qDebug("Тестирование завершено");
    }

};

#endif // TEST_PARSER_H
