#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <Recognizer.h>
#include <string>
#include <Parser_name_space.h>
#include <cstdlib>
#include <algorithm>

using std::cout;

/**
 * @brief The Parser class
 * Получает выражение для парсинга
 * Распознаёт лексемы указанные в cmd_operation по средствам методова toPars ,
 * Передаёт комманды и значения классу Recognizer который строит список и вычисляет распознанное выражение.
 * Проверяет на ошибки ввода данных  и их корректность
 * Проверяет: баланс скобок, открывающие скобки для функций, включение не распозаваемых лексем
 */
class Parser
{
private:
    double result;
    Recognizer * recognizer;
    std::string cmd_operation= "( + -_ * / ! ^ ) , sin cos tan ctan log ln asin acos sign mod sqrt exp";

    /**
     * @brief check_on_correct проверит одинаково ли количество открывающих и закрывающих скобок
     * @return
     */
    bool is_correct(std::string *r);

    /**
     * @brief sendCommandToTree передаёт комманду о построении дереву выражения
     * @param cmd команда для дерева
     */
    void sendCommandToTree(NSParser::cell_verb cmd);

    //DEBUG
    /**
     * @brief print_verb выводит в консоль значения полей cmd
     * @param cmd команда для дерева
     */
    void print_verb(NSParser::cell_verb cmd);


public:
    Parser();
    /**
     * @brief toPars производит парсинг выражения и отправляет
     * команды Recognizer о построении дерева
     * @param verb выражение для парсинга
     */
    bool toPars(std::string verb);

    /**
     * @brief get_result getter для this->result
     * @return
     */
    double get_result() const;
    ~Parser();
};

#endif // PARSER_H
