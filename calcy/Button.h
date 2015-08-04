#ifndef BUTTON_H
#define BUTTON_H

#include <QWidget>
#include <QPushButton>
#include <QString>

/**
 * @brief The Button class расширение QPushButton. Добавлена возможность передачи названия текста на кнопке
 * через сигнал send_name
 */
class Button : public QPushButton
{
    Q_OBJECT
protected:
    QString name;
public:
    explicit Button(QString name);

signals:
    /**
     * @brief send_name отправка названия кнопки
     * @param name название кнопки
     */
    void send_name(QString name);

public slots:
    /**
     * @brief emit_name запрос на передачу названия кнопки
     */
    void emit_name();

};

#endif // BUTTON_H
