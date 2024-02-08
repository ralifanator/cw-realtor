/**
 * @file dialogauthor.h
 * @brief Файл содержит определение класса dialogAuthor
 */

#ifndef DIALOGAUTHOR_H
#define DIALOGAUTHOR_H

#include <QDialog>

// Пространство имен для пользовательского интерфейса
namespace Ui {
    class dialogAuthor; ///< Класс определения диалогового окна автора
}

/**
 * @brief Класс dialogAuthor - наследует QDialog и предоставляет функциональность диалогового окна автора
 */
class dialogAuthor : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Конструктор класса
     * @param parent Родительский виджет диалогового окна (необязательный)
     */
    explicit dialogAuthor(QWidget *parent = nullptr);

    /**
     * @brief Деструктор класса
     */
    ~dialogAuthor();

private slots:
    /**
     * @brief слот on_pushButtonOk_clicked обрабатывает нажатие на кнопку "ОК" в диалоговом окне
     */
    void on_pushButtonOk_clicked();

private:
    Ui::dialogAuthor *ui; ///< Указатель на пользовательский интерфейс диалогового окна автора
};

#endif // DIALOGAUTHOR_H
