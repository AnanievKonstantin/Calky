#include "Recognizer.h"



void Recognizer::init()
{
    reselt_calculation=-666;
    head=nullptr;
    tail=nullptr;
    current_prioryty=0;
}

void Recognizer::clear_list()
{
    list_cell * tmp=head;
    while(head!=nullptr)
    {
        head=head->next;
        tmp->next=nullptr;
        tmp->prev=nullptr;
        delete(tmp);
        tmp=head;
    }
}

bool Recognizer::fill_cell(list_cell *cell, NSParser::cell_verb &cmd)
{
    cell->function=cmd.function;
    cell->operation=cmd.operation;
    cell->value=cmd.value;
    cell->cmd=cmd.cod_cmd;
    cell->priority=this->get_priority(cmd);
    return true;
}

int Recognizer::get_priority(NSParser::cell_verb &cmd)
{
    if(cmd.function!=-1)
    {
        return this->current_prioryty+NSParser::FUNC;
    }
    if(cmd.operation!=-1)
    {
        switch (cmd.operation) {
            case '+':case '-':  return this->current_prioryty+NSParser::PLUS_MINUS;
            case '*':case '/':  return this->current_prioryty+NSParser::MUL_DIVIDE;
            case '^':           return this->current_prioryty+NSParser::POW;
            case '!':           return this->current_prioryty+NSParser::FACT;
            default :
                //std::cout<<"ILLEGAL OPERATION IN <Recognizer::get_priority>\n";
                return -1;
        }
    }
    if(cmd.operation==-1 && cmd.function==-1)
    {
        return this->current_prioryty+NSParser::NUM;
    }
    //std::cout<<"ILLEGAL input gata IN <Recognizer::get_priority>\n";
    return -1;
}

void Recognizer::print_expression_list() const
{
    list_cell * tmp=head;

    std::cout<<"{\n";
    for(;tmp!=nullptr;tmp=tmp->next)
    {
        this->print_cell_list(tmp);
    }
    std::cout<<"}\n";
}

void Recognizer::print_cell_list(list_cell * cell) const
{
    std::cout<<"{";
    if(cell->function!=-1)
    {
        std::cout<<"Function:\t"<<cell->function<<",";
        switch (cell->function)
        {
            case NSParser::LOG:
                std::cout<<"Log,";
                break;
            case NSParser::LN:
                std::cout<<"Ln,";
                break;
            case NSParser::SIN:
                std::cout<<"Sin,";
                break;
            case NSParser::COS:
                std::cout<<"Cos,";
                break;
            case NSParser::ASIN:
                std::cout<<"Asin,";
                break;
            case NSParser::ACOS:
                std::cout<<"Acos,";
                break;
            case NSParser::TAN:
                std::cout<<"Tan,";
                break;
            case NSParser::CTAN:
                std::cout<<"Ctan,";
                break;
            case NSParser::SIGN:
                std::cout<<"Sign,";
                break;
            case NSParser::MODUL:
                std::cout<<"Modul,";
                break;
            case NSParser::SQRT:
                std::cout<<"Sqrt,";
                break;
            case NSParser::EXP:
                std::cout<<"Exp,";
                break;
        }
    }
    if(cell->operation!=-1)
    {
        std::cout<<"Operation:\t"<<cell->operation<<",";
    }
    if(cell->operation==-1 && cell->function==-1)
    {
        std::cout<<"Number:\t"<<cell->value<<",";
    }
    std::cout<<"Prioritet:\t"<<cell->priority;
    std::cout<<"}\n";
}

double Recognizer::calc_expression()
{
    list_cell * p_current       = head;
    list_cell * p_to_execute    = head;
    int max_prioritet           = 0;

    while(head!=tail)
    {
        p_current       = head;
        p_to_execute    = head;
        max_prioritet   = 0;
        while(p_current!=nullptr)
        {
            if(p_current->function!=-1 || p_current->operation!=-1)
            {
                if(p_current->priority>max_prioritet)
                {
                    max_prioritet=p_current->priority;
                    p_to_execute=p_current;
                }
            }
            p_current=p_current->next;
        }
        if(calc_operand(p_to_execute)==false)
        {
            break;
            return -1;
        }
    }

    return head->value;
}

bool Recognizer::remove_from_list(list_cell *to_delete)
{
    if(head==nullptr)
    {
        //std::cout<<"__ERROR__: IN <Recognizer::remove_from_list()> EMPTY_LIST\n";
        return false;
    }
    if(to_delete==head)
    {
        head=head->next;
        head->prev=nullptr;
        delete to_delete;
        return true;
    }
    if(to_delete==tail)
    {
        tail=tail->prev;
        tail->next=nullptr;
        delete to_delete;
        return true;
    }
    if(to_delete!=head && to_delete!=tail)
    {
        to_delete->prev->next=to_delete->next;
        to_delete->next->prev=to_delete->prev;
        delete to_delete;
        return true;
    }
    //std::cout<<"__ERROR__: IN <Recognizer::remove_from_list()> ILLEGAL_POINTER\n";
    return false;
}



bool Recognizer::calc_operand(list_cell *to_execute)
{
    if(to_execute->function!=-1)
    {
        switch(to_execute->function)
        {
            case NSParser::SIN:
                to_execute->next->value=std::sin(to_execute->next->value);
                remove_from_list(to_execute);
            return true;

            case NSParser::COS:
                to_execute->next->value=std::cos(to_execute->next->value);
                remove_from_list(to_execute);
            return true;

            case NSParser::TAN:
                to_execute->next->value=std::tan(to_execute->next->value);
                remove_from_list(to_execute);
            return true;

            case NSParser::CTAN:
                to_execute->next->value=std::cos(to_execute->next->value)/std::sin(to_execute->next->value);
                remove_from_list(to_execute);
            return true;

            case NSParser::ASIN:
                to_execute->next->value=std::asin(to_execute->next->value);
                remove_from_list(to_execute);
            return true;

            case NSParser::ACOS:
                to_execute->next->value=std::acos(to_execute->next->value);
                remove_from_list(to_execute);
            return true;

            case NSParser::SIGN:
                to_execute->next->value= - (to_execute->next->value);
                remove_from_list(to_execute);
            return true;

            case NSParser::MODUL:
                to_execute->next->value=std::fabs(to_execute->next->value);
                remove_from_list(to_execute);
            return true;

            case NSParser::LOG:
                to_execute->next->value=std::log10(to_execute->next->value);
                remove_from_list(to_execute);
                //remove_from_list(to_execute->next->next);
            return true;

            case NSParser::LN:
                to_execute->next->value=std::log(to_execute->next->value);
                remove_from_list(to_execute);
            return true;

            case NSParser::EXP:
                to_execute->next->value=std::exp(to_execute->next->value);
                remove_from_list(to_execute);
            return true;

            case NSParser::SQRT:
                to_execute->next->value=std::sqrt(to_execute->next->value);
                remove_from_list(to_execute);
            return true;

            //default:
                //std::cout<<"__ERROR__: IN <Recognizer::calc_operand()> UNEXPECTED FUNCTION VERB\n";


        }
    }
    if(to_execute->operation!=-1)
    {

        //унарный минус
        if(to_execute->operation=='-' &&
                (to_execute->prev == nullptr    ||
                 to_execute->prev->function!=-1 ||
                 to_execute->prev->operation!=-1)
                )
        {
            to_execute->next->value=-to_execute->next->value;
            remove_from_list(to_execute);
            return true;
        }

        if(to_execute->operation == '!')
        {
            if(to_execute->prev->value < 0 || to_execute->prev==nullptr)
                return false;
            to_execute->prev->value=fact(int(to_execute->prev->value));
            remove_from_list(to_execute);
            return true;
        }


        if(to_execute->prev==nullptr || to_execute->next==nullptr) return false;
        switch(to_execute->operation)
        {
            case '+':
                to_execute->prev->value=to_execute->prev->value + to_execute->next->value;
                to_execute->prev->priority=0;
                remove_from_list(to_execute->next);
                remove_from_list(to_execute);
            return true;

            case '-':
                //минус на два аргумента
                to_execute->prev->value=to_execute->prev->value - to_execute->next->value;
                to_execute->prev->priority=0;
                remove_from_list(to_execute->next);
                remove_from_list(to_execute);
                return true;

            case '*':
                to_execute->prev->value=to_execute->prev->value * to_execute->next->value;
                to_execute->prev->priority=0;
                remove_from_list(to_execute->next);
                remove_from_list(to_execute);
            return true;

            case '/':
                to_execute->prev->value=to_execute->prev->value / to_execute->next->value;
                to_execute->prev->priority=0;
                remove_from_list(to_execute->next);
                remove_from_list(to_execute);
            return true;

            case '^':
                to_execute->prev->value=std::pow(to_execute->prev->value,to_execute->next->value);
                to_execute->prev->priority=0;
                remove_from_list(to_execute->next);
                remove_from_list(to_execute);
            return true;

           // default:
                //std::cout<<"__ERROR__: IN <Recognizer::calc_operand()> UNEXPECTED OPERATION VERB\n";
        }
    }
    //std::cout<<"__ERROR__: IN <Recognizer::calc_operand()> UNEXPECTED VERB\n";
    return false;
}

double Recognizer::fact(int N)
{
    if(N>=500) return 0;

    if(N < 0)
        return 0;
    if (N == 0)
        return 1;
    else
        return N * fact(N - 1);
}

Recognizer::Recognizer()
{

}

Recognizer::~Recognizer()
{
    this->clear_list();
}


bool Recognizer::addElement(NSParser::cell_verb cmd)
{


    switch(cmd.cod_cmd)
    {
        case NSParser::BEGIN_CREATION:

            init();
            return true; //установить параметры на default

        case NSParser::END_CREATION:

            this->print_expression_list();
            this->reselt_calculation=this->calc_expression();
            this->print_expression_list();
            clear_list();//почистить существующее дерево
            //std::cout<<std::fixed<<"Result: "<<reselt_calculation<<"\n";

            return true; //Вызвать функцию расчета результата
        case NSParser::OPEN_BRACKET:    this->current_prioryty+=5; return true;
        case NSParser::CLOSE_BRACKET:   this->current_prioryty-=5; return true;

    }

    if(this->head==nullptr)
    {
        head=new list_cell;
        this->fill_cell(head,cmd);
        head->next=nullptr;
        head->prev=nullptr;
        tail=head;
        return true;
    }
    else{
        tail->next=new list_cell;
        tail->next->prev=tail;
        tail=tail->next;
        tail->next=nullptr;
        this->fill_cell(tail,cmd);
        return true;
    }

    return false;
}

double Recognizer::get_result() const
{
    return reselt_calculation;
}





























