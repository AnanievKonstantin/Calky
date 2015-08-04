#ifndef PARSER_NAME_SPACE_H
#define PARSER_NAME_SPACE_H
#include <string>

/**
 *Пространство имён содержащее обьявления
 *необходимых структур для парсера и recognizer
 */
namespace NSParser
{
    /**
     * Перечисление команд для исполнения
     */
    enum recognizer_command
    {
        BEGIN_CREATION,     //Начать построение
        END_CREATION,       //Конец построения
        OPEN_BRACKET,       //Открывающая скобка
        CLOSE_BRACKET,      //закрывающая скоюка
        OPERATION,          //передача операции +-/*^! - созжание узла с операцией
        FUNCTION,           //Создание узла с функцией sin,cos...
        NUMBER              //Создание узла с числом
    };

    /**
     * @brief The prioriry enum приоритеты операций
     */
    enum prioriry{
        NUM,
        PLUS_MINUS,
        MUL_DIVIDE,
        POW,
        FACT,
        FUNC
    };

    /**
     * @brief The func_to_exec enum
     * перечисление всех функций доступных в программе
     */
    enum func_to_exec{
        SIN,COS,ASIN,ACOS,TAN,CTAN,LN,LOG,SIGN,MODUL,EXP,SQRT
    };



    /**
     * @brief The cell_verb struct
     * Структура команды передаваемая дереву
     * для его построения
     */
    struct cell_verb
    {
        int cod_cmd;            //from enum recognizer_command
        int function;           //from func_to_exec enum
        char operation;          //для +-*/^
        double value;           //Значение числа при cod_cmd=NUMBER
    };
}


#endif // PARSER_NAME_SPACE_H
