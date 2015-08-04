#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include "Parser.h"

/**
 * @brief The Model class
 * Реализует модель парсинга математических выражений и их расчета, а так же имеет сигналы и слоты
 * для передачи данных между View и Model и работы с ячейкой памяти калькулятора.
 */
class Model : public QObject
{
    Q_OBJECT
protected:
    Parser  * calc_parser;
    QString * calc_memory;

public:
    explicit Model(QObject *parent = 0);
    ~Model();

signals:
    /**
     * @brief signal_send_result передает результат вычисления распарсеннгого выражения
     * @param result_calc резальтат вычислений
     */
    void signal_send_result(QString result_calc);

    /**
     * @brief signal_send_memory передает данные из памяти
     * @param current_memory текущение данные в памяти
     */
    void signal_send_memory(QString current_memory);
public slots:

    /**
     * @brief slot_calculation передаёт выражение для парсинга и последующего вычисления
     * @param str_to_calc выражение для вычисления
     */
    void slot_calculation(QString str_to_calc);

    /**
     * @brief slot_set_memory записывает в память (calc_memory) переданные данные
     * @param str_to_mem выражение для записи
     */
    void slot_set_memory(QString str_to_mem);

    /**
     * @brief slot_call_send_memory вызов сигнала signal_send_memory
     */
    void slot_call_send_memory();

};

#endif // MODEL_H
