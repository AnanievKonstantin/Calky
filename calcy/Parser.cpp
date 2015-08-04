#include "Parser.h"

bool Parser::is_correct(std::string * r)
{
    int count=0;
    std::string::const_iterator iter = r->begin();
    for(;iter<r->end();iter++)
    {
        if(*iter == '(')
        {
             count++;
             continue;
        }
        if(*iter == ')')
        {
             count--;
             continue;
        }
    }
    if(count == 0) return true;

    return false;
}

void Parser::sendCommandToTree(NSParser::cell_verb cmd)
{
    this->recognizer->addElement(cmd);
}

void Parser::print_verb(NSParser::cell_verb cmd)
{
    cout<<"Command: "         <<'\n'
       <<'\t'<<"cod: "        <<cmd.cod_cmd<<'\n'
       <<'\t'<<"operation: "  <<cmd.operation<<'\n'
       <<'\t'<<"function: "  <<cmd.function<<'\n'
       <<'\t'<<"value: "      <<cmd.value<<'\n';
}

Parser::Parser()
{
    this->recognizer    = new Recognizer();
}

bool Parser::toPars(std::string verb)
{
    //std::cout<<"Parsing: <"<<verb<<"> "<<std::endl;

    this->sendCommandToTree({NSParser::BEGIN_CREATION,-1,'@',-1});

    string::iterator iter = verb.begin();
    if(is_correct(&(verb)))
    {
        //std::cout<<"Баланс скобок учтён"<<'\n';

        if(verb.size()==0)
        {
            cout<<"Пустое выражение\n";
            return false;
        }
        //std::cout<<"Начало выражения"<<'\n';
        //this->sendCommandToTree({-1,-1,-1,100});

        for(;iter<verb.end();++iter)
        {
            if(std::isdigit(*iter))
            {
                string::iterator tmp=iter;
                while(std::isdigit(*tmp)) ++tmp;

                if(*tmp == '.')
                {
                    //cout<<"\tЧисло c плавающей точков: "<<std::stod(&(*iter))<<'\n';
                    this->sendCommandToTree({NSParser::NUMBER,-1,-1,std::stod(&(*iter))});
                    while(std::isdigit(*iter)) iter++;
                    iter++;//пропустить точку
                    while(std::isdigit(*iter)) iter++;
                    iter--;

                    continue;
                }
                else{
                    //cout<<"\tЧисло цело: "<<std::stoi(&(*iter))<<'\n';
                    this->sendCommandToTree({NSParser::NUMBER,-1,-1,std::stoi(&(*iter))});
                    while(std::isdigit(*iter)) iter++;
                    iter--;
                    continue;
                }

            }
            if(cmd_operation.find(*iter) != std::string::npos)
            {
                //cout<<"In"<<*iter<<'\n';
                switch (*iter)
                {
                    case '+':case '-':
                    case '*':case '/':
                    case ',':
                        //cout<<"\tОперация: "<<*iter<<'\n';
                        this->sendCommandToTree({NSParser::OPERATION,-1,*iter,-1});
                        continue;
                    case '!':case '^':
                        //cout<<"\t Унарная операция: "<<*iter<<'\n';
                        this->sendCommandToTree({NSParser::OPERATION,-1,*iter,-1});
                        continue;
                    case '(':
                        this->sendCommandToTree({NSParser::OPEN_BRACKET,-1,-1,-1});
                        continue;
                    case ')':
                        this->sendCommandToTree({NSParser::CLOSE_BRACKET,-1,-1,-1});
                        continue;
                }

                if(*iter == 'l')
                {
                    if(*(iter+1) == 'o')
                    {
                        //cout<<"\tФункция: "<<"log"<<'\n';
                        if(*(iter+3) != '(')
                        {
                            //cout<<"Error open ( in log"<<'\n';
                            return false;
                        }
                        this->sendCommandToTree({NSParser::FUNCTION,NSParser::LOG,-1,-1});
                        iter+=2;
                        continue;

                    }
                    if(*(iter+1) == 'n')
                    {
                        //cout<<"\tФункция: "<<"ln"<<'\n';
                        if(*(iter+2) != '(')
                        {
                            //cout<<"Error open ( in ln"<<'\n';
                            return false;
                        }
                        this->sendCommandToTree({NSParser::FUNCTION,NSParser::LN,-1,-1});
                        iter+=1;
                        continue;
                    }
                }
                if(*iter == 'c')
                {
                    if(*(iter+1) == 'o')
                    {
                        //cout<<"\tФункция: "<<"cos"<<'\n';
                        if(*(iter+3) != '(')
                        {
                            //cout<<"Error open ( in cos"<<'\n';
                            return false;
                        }
                        this->sendCommandToTree({NSParser::FUNCTION,NSParser::COS,-1,-1});
                        iter+=2;
                        continue;
                    }
                    if(*(iter+1) == 't')
                    {
                        //cout<<"\tФункция: "<<"ctan"<<'\n';
                        if(*(iter+4) != '(')
                        {
                             cout<<"Error open ( in ctg"<<'\n';
                             return false;
                        }
                        this->sendCommandToTree({NSParser::FUNCTION,NSParser::CTAN,-1,-1});
                        iter+=3;
                        continue;
                    }
                }
                if(*iter == 's' && *(iter+1) == 'i')
                {
                    if(*(iter+2) == 'n' )
                    {
                        //cout<<"\tФункция: "<<"sin"<<'\n';
                        if(*(iter+3) != '(')
                        {
                             //cout<<"Error open ( in sin"<<'\n';
                             return false;
                        }
                        this->sendCommandToTree({NSParser::FUNCTION,NSParser::SIN,-1,-1});
                        iter+=2;
                        continue;
                    }
                }
                if(*iter == 't')
                {
                    if(*(iter+1) == 'a')
                    {
                        //cout<<"\tФункция: "<<"tan"<<'\n';
                        if(*(iter+3) != '(')
                        {
                            cout<<"Error open ( in tan"<<'\n';
                            return false;
                        }
                        this->sendCommandToTree({NSParser::FUNCTION,NSParser::TAN,-1,-1});
                        iter+=2;
                        continue;
                    }
                }
                if(*iter == 's')
                {
                    if(*(iter+1) == 'i' && *(iter+2) == 'g' )
                    {
                        //cout<<"\tФункция: "<<"sign"<<'\n';
                        if(*(iter+4) != '(')
                        {
                             //cout<<"Error open ( in sign"<<'\n';
                             return false;
                        }
                        this->sendCommandToTree({NSParser::FUNCTION,NSParser::SIGN,-1,-1});
                        iter+=3;
                        continue;
                    }
                }
                if(*iter == 'a')
                {
                    if(*(iter+1) == 's')
                    {
                        //cout<<"\tФункция: "<<"asin"<<'\n';
                        if(*(iter+4) != '(')
                        {
                            //cout<<"Error open ( in asin"<<'\n';
                            return false;
                        }
                        this->sendCommandToTree({NSParser::FUNCTION,NSParser::ASIN,-1,-1});
                        iter+=3;
                        continue;
                    }
                    if(*(iter+1) == 'c')
                    {
                        //cout<<"\tФункция: "<<"acos"<<'\n';
                        if(*(iter+4) != '(')
                        {
                            //cout<<"Error open ( in acos"<<'\n';
                            return false;
                        }
                        this->sendCommandToTree({NSParser::FUNCTION,NSParser::ACOS,-1,-1});
                        iter+=3;
                        continue;
                    }
                }
                if(*iter == 'm' && *(iter+1)=='o' && *(iter+2)=='d')
                {
                    //cout<<"\tФункция mod\n";
                    if(*(iter+3)!='(')
                    {
                         //cout<<"Error open ( in mod\n";
                         return false;
                    }
                    this->sendCommandToTree({NSParser::FUNCTION,NSParser::MODUL,-1,-1});
                    iter+=2;
                    continue;

                }
                if(*iter == 's' && *(iter+1)=='q' && *(iter+2)=='r' && *(iter+3)=='t')
                {
                    //cout<<"\tФункция sqrt\n";
                    if(*(iter+4)!='(')
                    {
                         //cout<<"Error open ( in sqrt\n";
                         return false;
                    }
                    this->sendCommandToTree({NSParser::FUNCTION,NSParser::SQRT,-1,-1});
                    iter+=3;
                    continue;
                }
                if(*iter == 'e' && *(iter+1)=='x' && *(iter+2)=='p')
                {
                    //cout<<"\tФункция exp\n";
                    if(*(iter+3)!='(')
                    {
                         //cout<<"Error open ( in exp\n";
                         return false;
                    }
                    this->sendCommandToTree({NSParser::FUNCTION,NSParser::EXP,-1,-1});
                    iter+=2;
                    continue;
                }

                //cout<<"_ERROR_: не существующая функция"<<'\n';
                return false;
            }
            //cout<<"_ERROR_: не существующий оператор"<<'\n';
            return false;
        }
    }else{
        //cout<<"_ERROR_: нарушен баланс скобок"<<'\n';
        return false;
    }
    //cout<<"Конец выражения"<<"\n";
    this->sendCommandToTree({NSParser::END_CREATION,-1,'@',-1});
    result=this->recognizer->get_result();
    return true;
}

double Parser::get_result() const
{
    return this->result;
}

Parser::~Parser()
{
    delete this->recognizer;
}
