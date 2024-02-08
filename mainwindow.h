#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>

#include <QDebug>
#include <QMessageBox>
#include <QSettings>
#include <QComboBox>
#include <QTableView>
#include "QStandardItemModel"
#include "QSqlRelationalTableModel"
#include "QStandardItem"
#include "QSqlDatabase"
#include "QSqlTableModel"
#include "QStatusBar"
#include "QSortFilterProxyModel"

#include <QList>
#include <QEvent>
#include <QTranslator>
#include <QDir>
#include <QLibraryInfo>
#include <QMimeData>
#include "model.h"

namespace Ui {
class MainWindow;
}

class QActionGroup;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QSqlDatabase db;


private slots:
    void on_actionConnect_triggered();

    void on_actionDisconnect_triggered();

    void on_actionEdit_row_triggered();

    void on_actionAdd_row_triggered();

    void on_actionDelete_row_triggered();

    void on_actionAbout_the_author_triggered();

    void switchLanguage(QAction *action);

    void on_buttonQuery_clicked();

    void on_pushButtonSearch_clicked();

private:
    Ui::MainWindow *ui;
    modell *model;
    void enablingElements(bool);
    void readSettings();
    void writeSettings();
    void enablingEditing(bool);
    void notSelected();
    void deleting(int);
    bool verify(int);
    void adding(QString, QString, QString, QString, QString, QString, QString);
    void editing(QString, QString, QString, QString, QString, QString, QString, int);
    QTranslator appTranslator;
    QTranslator qtTranslator;
    QActionGroup *languageActionGroup;
    QString qmPath;
    void createLanguageMenu();
    void setupModel();
};

#endif // MAINWINDOW_H
