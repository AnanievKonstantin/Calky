#include "Control.h"

void Control::set_event_to_button(QList<Button *> * list)
{
    QList<Button*>::iterator i = list->begin();
    for(;i<list->end();i++)
    {
        QObject::connect(*i,SIGNAL(clicked()),
                         *i,SLOT(emit_name()));
        QObject::connect(*i,SIGNAL(send_name(QString)),
                    this->calc_line_edit,SLOT(slot_append_text(QString)));
    }
}

void Control::create_model_and_viewer_interface(Button *calculation_button,Button * mem_plus_button,Button * mem_minus_button)
{
    //--------для кнопки равно
    /*
     * @brief QObject::connect
     * нажатие на копку =
     * бращается к текстовой линии для вызова сигнала о отправке текста send_text(QString)
     * для передачи в calc_model,SLOT(slot_calculation(QString))) текущего выражения в текстовой линии
     */
    QObject::connect(calculation_button,SIGNAL(clicked()),
                     this->calc_line_edit,SLOT(slot_call_signal_send_text()));
    /*
     * @brief QObject::connect
     * передача значения из текстовой линии в парсер - calc_model
     */
    QObject::connect(calc_line_edit,SIGNAL(send_text(QString)),
                     this->calc_model,SLOT(slot_calculation(QString)));
    /*
     * @brief QObject::connect
     * передача результата вычислений в calc_line_edit
     */
    QObject::connect(this->calc_model,SIGNAL(signal_send_result(QString)),
                     this->calc_line_edit,SLOT(setText(QString)));
    //----------

    //M+ and M- button
    QObject::connect(mem_plus_button,SIGNAL(clicked()),
                     this->calc_line_edit,SLOT(slot_call_send_text_in_memory()));
    QObject::connect(this->calc_line_edit,SIGNAL(send_text_in_memory(QString)),
                     this->calc_model,SLOT(slot_set_memory(QString)));

    QObject::connect(mem_minus_button,SIGNAL(clicked()),
                     this->calc_model,SLOT(slot_call_send_memory()));

    QObject::connect(this->calc_model,SIGNAL(signal_send_memory(QString)),
                     this->calc_line_edit,SLOT(setText(QString)));
}



Control::Control(QObject *parent) :
    QObject(parent)
{
    this->calc_win          = new Window();
    this->calc_model        = new Model();
    this->calc_line_edit    = new TextEdit;
    this->win_main_layout   = new QGridLayout;

    this->buttons_numbers       = new QList<Button*>;
    this->buttons_functions     = new QList<Button*>;
    this->buttons_operations    = new QList<Button*>;
    this->advanced_button       = new QList<Button*>;

    Button * b0        = new Button("0");
    Button * b1        = new Button("1");
    Button * b2        = new Button("2");
    Button * b3        = new Button("3");
    Button * b4        = new  Button("4");
    Button * b5        = new  Button("5");
    Button * b6        = new  Button("6");
    Button * b7        = new  Button("7");
    Button * b8        = new  Button("8");
    Button * b9        = new  Button("9");
    Button * b_M_plus  = new  Button("M+");
    Button * b_M_minus = new  Button("M-");
    Button * b_mul     = new  Button("*");
    Button * b_div     = new  Button("/");
    Button * b_plus    = new  Button("+");
    Button * b_minus   = new  Button("-");
    Button * b_power   = new  Button("^");
    Button * b_fact    = new  Button("!");
    Button * b_sin     = new  Button("sin()");
    Button * b_cos     = new  Button("cos()");
    Button * b_tan     = new  Button("tan()");
    Button * b_ctan    = new  Button("ctan()");
    Button * b_asin    = new  Button("asin()");
    Button * b_acos    = new  Button("acos()");
    Button * b_exp     = new  Button("exp()");
    Button * b_ln      = new  Button("ln()");
    Button * b_log     = new  Button("log()");
    Button * b_mod     = new  Button("mod()");
    Button * b_sqrt    = new  Button("sqrt()");
    Button * b_calc    = new  Button("=");
    Button * b_clear    = new  Button("clear");

    advanced_button->append(b_clear);
    advanced_button->append(b_calc);
    advanced_button->append(b_M_minus);
    advanced_button->append(b_M_minus);

    buttons_numbers->append(b0);
    buttons_numbers->append(b1);
    buttons_numbers->append(b2);
    buttons_numbers->append(b3);
    buttons_numbers->append(b4);
    buttons_numbers->append(b5);
    buttons_numbers->append(b6);
    buttons_numbers->append(b7);
    buttons_numbers->append(b8);
    buttons_numbers->append(b9);

    buttons_operations->append(b_mul);
    buttons_operations->append(b_div);
    buttons_operations->append(b_plus);
    buttons_operations->append(b_minus);
    buttons_operations->append(b_power);
    buttons_operations->append(b_fact);

    buttons_functions->append(b_sin);
    buttons_functions->append(b_cos);
    buttons_functions->append(b_tan);
    buttons_functions->append(b_ctan);
    buttons_functions->append(b_asin);
    buttons_functions->append(b_acos);
    buttons_functions->append(b_exp);
    buttons_functions->append(b_ln);
    buttons_functions->append(b_log);
    buttons_functions->append(b_mod);
    buttons_functions->append(b_sqrt);

    win_main_layout->addWidget(calc_line_edit,0,0,1,3);
    win_main_layout->addWidget(b0,5,1);

    win_main_layout->addWidget(b1,2,0);
    win_main_layout->addWidget(b2,2,1);
    win_main_layout->addWidget(b3,2,2);

    win_main_layout->addWidget(b4,3,0);
    win_main_layout->addWidget(b5,3,1);
    win_main_layout->addWidget(b6,3,2);

    win_main_layout->addWidget(b7,4,0);
    win_main_layout->addWidget(b8,4,1);
    win_main_layout->addWidget(b9,4,2);

    win_main_layout->addWidget(b_M_minus,7,0);
    win_main_layout->addWidget(b_M_plus,6,0);
    win_main_layout->addWidget(b_mul,6,1);
    win_main_layout->addWidget(b_div,7,1);

    win_main_layout->addWidget(b_plus,6,2);
    win_main_layout->addWidget(b_minus,7,2);
    win_main_layout->addWidget(b_power,10,0);
    win_main_layout->addWidget(b_fact,10,0);
    win_main_layout->addWidget(b_sin);
    win_main_layout->addWidget(b_cos);
    win_main_layout->addWidget(b_tan);
    win_main_layout->addWidget(b_ctan);
    win_main_layout->addWidget(b_asin);
    win_main_layout->addWidget(b_acos);
    win_main_layout->addWidget(b_exp);
    win_main_layout->addWidget(b_ln);
    win_main_layout->addWidget(b_log);
    win_main_layout->addWidget(b_mod);
    win_main_layout->addWidget(b_sqrt);
    win_main_layout->addWidget(b_calc,16,0,1,3);
    win_main_layout->addWidget(b_clear,5,2);

    this->set_event_to_button(buttons_numbers);
    this->set_event_to_button(buttons_operations);
    this->set_event_to_button(buttons_functions);

    this->create_model_and_viewer_interface(b_calc,b_M_plus,b_M_minus);

    //установка события отчистки экрана на клик по копке clear
    QObject::connect(b_clear,SIGNAL(clicked()),
                     this->calc_line_edit,SLOT(slot_clear_text()));

    calc_win->setLayout(win_main_layout);
    calc_win->show();
}

Control::~Control()
{
    delete buttons_numbers;
    delete buttons_functions;
    delete buttons_operations;
    delete advanced_button;
    delete calc_model;
    delete calc_win;
    delete calc_line_edit;
    delete win_main_layout;

}
