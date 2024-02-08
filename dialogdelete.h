/**
 * @file dialogdelete.h
 * @brief Файл содержит определение класса dialogDelete
 */

#ifndef DIALOGDELETE_H
#define DIALOGDELETE_H

#include <QDialog>

// Пространство имен для пользовательского интерфейса
namespace Ui {
    class dialogDelete; ///< Класс определения диалогового окна удаления
}

/**
 * @brief Класс dialogDelete - наследует QDialog и предоставляет функциональность диалогового окна удаления
 */
class dialogDelete : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Конструктор класса
     * @param parent Родительский виджет диалогового окна (необязательный)
     */
    explicit dialogDelete(QWidget *parent = nullptr);

    /**
     * @brief Деструктор класса
     */
    ~dialogDelete();

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
    Ui::dialogDelete *ui; ///< Указатель на пользовательский интерфейс диалогового окна удаления
};

#endif // DIALOGDELETE_H
