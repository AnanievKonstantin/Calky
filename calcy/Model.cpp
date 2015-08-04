#include "Model.h"

Model::Model(QObject *parent) :
    QObject(parent)
{
    this->calc_parser   = new Parser;
    this->calc_memory   = new QString("");
}


Model::~Model()
{
    delete this->calc_parser;
    delete this->calc_memory;
}

void Model::slot_calculation(QString str_to_calc)
{
    if(this->calc_parser->toPars(str_to_calc.toStdString()) == true)
    {
        emit signal_send_result(QString::number(calc_parser->get_result(),'g',300));
    }
    else{
        emit signal_send_result("__ERROR__");
    }
}

void Model::slot_set_memory(QString str_to_mem)
{
    *this->calc_memory=str_to_mem;
}

void Model::slot_call_send_memory()
{
    this->signal_send_memory(*this->calc_memory);
}
