#ifndef RECOGNIZER_H
#define RECOGNIZER_H

#include <Parser_name_space.h>
#include <string>
#include <stack>
#include <iostream>
#include <cmath>

using std::string;
/**
 * @brief The list_cell struct
 * узел двунапрвленного списка
 */
struct list_cell{

    double value        =666;
    char operation      ='@';
    int function        =-1;
    int cmd             =-1;
    int priority        = 0;

    list_cell * next    =nullptr;
    list_cell * prev   =nullptr;

};

/**
 * @brief The Recognizer class
 * Получает команду от парсера и строит список
 * после чего расчитывает значение выражения в списке
 * результат поместит в
 * reselt_calculation
 */
class Recognizer
{

private:
    double reselt_calculation=-666;
    list_cell * head=nullptr;
    list_cell * tail=nullptr;
    int current_prioryty=0;

    /**
     * @brief init инициация значений по умолчанию для начала работы и сознания нового списка
     */
    void init();

    /**
     * @brief clear_list удаление текущего списка
     */
    void clear_list();

    /**
     * @brief fill_cell заполнение ячейки списка  cell переданными значениями из cmd, установка приоритета лексеме
     * @param cell указатель на еще пустую ячейку списка
     * @param cmd команда от Parser с указаниями данных для построения ячейки
     * @return
     */
    bool fill_cell(list_cell * cell,NSParser::cell_verb & cmd);

    /**
     * @brief get_priority получение приоритеты операции по её типу
     * @param cmd структура содержащая информацию о лексеме
     * @return приоритет операции
     */
    int get_priority(NSParser::cell_verb &cmd);

    /**
     * @brief print_expression_list вывод списка для вычисления на экран
     */
    void print_expression_list() const;

    /**
     * @brief print_cell_list вывод переданной ячейки списка
     * @param cell
     */
    void print_cell_list(list_cell * cell) const;

    /**
     * @brief calc_expression вычисляет данные находящиеся в списке
     * @return результат вычислений, если обнаружена ошибка вернёт -1
     */
    double calc_expression();

    /**
     * @brief remove_from_list удаление элемента списка по указателю
     * @param to_delete указатель на ячейку списка, которая подлежит удалению
     * @return true если всё прошло успешно, false усли возникла ошибка
     */
    bool remove_from_list(list_cell * to_delete);
    /**
     * @brief calc_operand идентифицирует операцию и преобразует список
     * заменяя операнд и его аргументы на одну яцейку типа NUMBER c приоритетом NUM
     * @param to_execute указатель на операнд (функция или операция)
     * @return true если все прошло успешно
     */
    bool calc_operand(list_cell * to_execute);

    /**
     * @brief fact вычисляет факториал от числа
     * @param N число для взятия факториала
     * @return  если N<0 вернёт ноль, если N>500 вернет 0
     */
    double fact(int N);


public:
    Recognizer();
    ~Recognizer();
    /**
     * @brief addElement добавление элемента в список или его создание в случае пустого списка
     * @param cmd команда для построения
     * @return  true если всё прошло хорошо и элемент добовлен
     */
    bool addElement(NSParser::cell_verb cmd);

    /**
     * @brief get_result вернетрезультат вычислений
     * @return
     */
    double get_result() const;
};

#endif // RECOGNIZER_H
