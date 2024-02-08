/**
 * @file dialogredaction.h
 * @brief Файл содержит определение класса dialogRedaction
 */

#ifndef DIALOGREDACTION_H
#define DIALOGREDACTION_H

#include <QDialog>

// Пространство имен для пользовательского интерфейса
namespace Ui {
    class dialogRedaction; ///< Класс определения диалогового окна редакции
}

/**
 * @brief Класс dialogRedaction - наследует QDialog и предоставляет функциональность диалогового окна редакции
 */
class dialogRedaction : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Конструктор класса
     * @param parent Родительский виджет диалогового окна (необязательный)
     */
    explicit dialogRedaction(QWidget *parent = nullptr);

    /**
     * @brief Деструктор класса
     */
    ~dialogRedaction();

    /**
     * @brief Получение значений полей из диалогового окна
     * @param[in,out] param1 Значение первого поля
     * @param[in,out] param2 Значение второго поля
     * @param[in,out] param3 Значение третьего поля
     * @param[in,out] param4 Значение четвертого поля
     * @param[in,out] param5 Значение пятого поля
     * @param[in,out] param6 Значение шестого поля
     * @param[in,out] param7 Значение шестого поля
     */
    void getData(QString& param1, QString& param2, QString& param3, QString& param4, QString& param5, QString& param6, QString& param7);

    /**
     * @brief Устанавливает текст на метке (label) диалогового окна
     * @param text Текст, который будет установлен на метке
     */
    void editLabel(QString text);

private slots:
    /**
     * @brief слот on_pushButtonOk_clicked обрабатывает нажатие на кнопку "ОК" в диалоговом окне
     */
    void on_pushButtonOk_clicked();

    /**
     * @brief слот on_pushButtonCancel_clicked обрабатывает нажатие на кнопку "Отмена" в диалоговом окне
     */
    void on_pushButtonCancel_clicked();

private:
    Ui::dialogRedaction *ui; ///< Указатель на пользовательский интерфейс диалогового окна редакции
};

#endif // DIALOGREDACTION_H
