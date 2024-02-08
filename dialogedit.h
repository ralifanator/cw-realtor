/**
 * @file dialogedit.h
 * @brief Файл содержит определение класса dialogEdit
 */

#ifndef DIALOGEDIT_H
#define DIALOGEDIT_H

#include <QDialog>

// Пространство имен для пользовательского интерфейса
namespace Ui {
    class dialogEdit; ///< Класс определения диалогового окна редактирования
}

/**
 * @brief Класс dialogEdit - наследует QDialog и предоставляет функциональность диалогового окна редактирования
 */
class dialogEdit : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Конструктор класса
     * @param parent Родительский виджет диалогового окна (необязательный)
     */
    explicit dialogEdit(QWidget *parent = nullptr);

    /**
     * @brief Деструктор класса
     */
    ~dialogEdit();

    /**
     * @brief Получение числового значения, введенного пользователем
     * @return Введенное число
     */
    int num();

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
    Ui::dialogEdit *ui; ///< Указатель на пользовательский интерфейс диалогового окна редактирования
};

#endif // DIALOGEDIT_H
