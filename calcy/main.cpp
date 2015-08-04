#include "Control.h"
#include <QApplication>

/**
 * @brief main
 * Калькулятор с поддержкой следующих лексем:
 * ( + - * / ! ^ )  sin cos tan ctan log ln asin acos sign mod sqrt exp.
 * Производит вычисление с учетом приоритета операций и скобок.
 * Ввод скобок производится в ручную. M+ M- отвечают за хранение текущего выражения.
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Control * control = new Control(&a);

    return a.exec();
}
