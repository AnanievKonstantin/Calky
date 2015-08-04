#ifndef CONTROL_H
#define CONTROL_H

#include <QObject>
#include "Window.h"
#include "Model.h"
#include "QGridLayout"
#include "Textedit.h"
#include <QDebug>
#include <Button.h>
#include <QList>

/**
 * @brief The Control class
 * создает рабочее окно калькулятора, модель для обработки математичесикх выражений
 * распределяет сигналы и события для взаимодействия пользовательского интерфейса с моделью
 */
class Control : public QObject
{
    Q_OBJECT
protected:
    Window                  * calc_win;
    Model                   * calc_model;
    TextEdit                * calc_line_edit;
    QGridLayout             * win_main_layout;
    QList<Button*>          * buttons_operations;
    QList<Button*>          * buttons_functions;
    QList<Button*>          * buttons_numbers;
    QList<Button*>          * advanced_button;


    /**
     * @brief set_event_to_button создает взаимодействие между переданными кнопками и полем ввода выражения
     * при нажатии кнопки в поле жля ввода выводится её название
     * @param list книпки названия которых нужно выводить в calc_line_edit
     */
    void set_event_to_button(QList<Button *> * list);

    /**
     * @brief create_model_and_viewer_interface определяет действия, которые произайду  при нажатии кнопок
     * '=','M+','M-' между моделью и textEdit
     * @param calculation_button кнопка передачи выражения в model
     * @param mem_plus_button кнопка добавления выражения в память
     * @param mem_minus_button кнопка вывода данных из памяти и выводом их на экран, стирая предыдущее содержимое.
     * Данные в памяти остаются сохранены
     */
    void create_model_and_viewer_interface(Button * calculation_button, Button *mem_plus_button, Button *mem_minus_button);
    //Debug
public:
    explicit Control(QObject *parent = 0);
    ~Control();



signals:

public slots:

};

#endif // CONTROL_H
