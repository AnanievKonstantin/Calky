#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#include <QLineEdit>
#include <QString>

/**
 * @brief The TextEdit class расширение QLineEdit для
 * возможности получения данных из текстового поля и их добавления по средствам сигналов.
 */
class TextEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit TextEdit(QWidget *parent = 0);

signals:
    /**
     * @brief send_text передача текста по средствам сигнала
     */
    void send_text(QString);

    /**
     * @brief send_text_in_memory передача текста по средствам сигнала. Сигнал нужен для отсылки данных в память
     */
    void send_text_in_memory(QString);
public slots:

    /**
     * @brief slot_append_text добавление текста к существующему в текстовой линии. Жлбавление с права.
     * @param text
     */
    void slot_append_text(QString text);

    /**
     * @brief slot_call_signal_send_text вызов сигнала send_text
     */
    void slot_call_signal_send_text();

    /**
     * @brief slot_call_signal_send_text вызов сигнала send_text_in_memory
     */
    void slot_call_send_text_in_memory();

    /**
     * @brief slot_clear_text слот для вызова отчистки текстового поля
     */
    void slot_clear_text();

};

#endif // TEXTEDIT_H
