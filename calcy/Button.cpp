#include "Button.h"

Button::Button(QString name):QPushButton(name)
{
    this->name=name;
}

void Button::emit_name()
{
    emit send_name(this->name);
}
