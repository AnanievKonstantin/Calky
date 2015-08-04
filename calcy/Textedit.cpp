#include "Textedit.h"

TextEdit::TextEdit(QWidget *parent) :
    QLineEdit(parent)
{
}

void TextEdit::slot_append_text(QString text)
{
    this->insert(text);
}

void TextEdit::slot_call_signal_send_text()
{
    emit this->send_text(this->text());
}

void TextEdit::slot_call_send_text_in_memory()
{
    emit this->send_text_in_memory(this->text());
}

void TextEdit::slot_clear_text()
{
    this->setText("");
}
