#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "dialogdelete.h"
#include "dialogedit.h"
#include "dialogredaction.h"
#include "dialogauthor.h"
#include "model.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    model(new modell)
{
    ui->setupUi(this);
    setWindowTitle(tr("cw-realtor"));
    ui->tableView->setSortingEnabled(true);
    ui->tableView->setDragEnabled(true);
    ui->tableView->setDropIndicatorShown(true);
    //enablingElements(false);
    enablingEditing(false);
    setAcceptDrops(true);
    readSettings();

    if (QSqlDatabase::isDriverAvailable("QPSQL"))
        qDebug() << "SUCCESS: PostgreSQL database driver found!";
    else
        qDebug() << "FAILURE: No postgreSQL database driver available!";

    qApp->installTranslator(&appTranslator);
    qApp->installTranslator(&qtTranslator);
    qmPath = qApp->applicationDirPath() + "/tr";
    qDebug() << "qmPath: " << qmPath;
    createLanguageMenu();
}

MainWindow::~MainWindow()
{
    writeSettings();
    delete ui;
}

void MainWindow::readSettings() {
    QSettings settings("Home","cw-realtor");
    settings.beginGroup("MainWindowGeometry");
    resize(settings.value("size", QSize(400, 500)).toSize());
    move(settings.value("pos", QPoint(200, 200 )).toPoint());
}

void MainWindow::writeSettings() {
    QSettings settings("Home","cw-realtor");
    settings.beginGroup("MainWindowGeometry");
    settings.setValue("size", size());
    settings.setValue("pos", pos());
    settings.endGroup();
}

void MainWindow::on_actionConnect_triggered()
{
    db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("192.168.99.10"); // хост
    db.setDatabaseName("realtor"); // бд
    db.setPort(5432); // порт
    db.setConnectOptions("requiressl=1;connect_timeout=2");
    db.setUserName("postgres"); // пользователь
    db.setPassword("ralif"); // пароль

    // проверка подключения
    if (db.open()) {
        qDebug() << "Connect success!";
        enablingElements(true);
    }
    else {
        qDebug() << "Connect fail: " << db.lastError().text();
    }
}

void MainWindow::enablingElements(bool b) {
    ui->comboBox->setEnabled(b);
    ui->buttonQuery->setEnabled(b);
    ui->actionConnect->setEnabled(!b);
    ui->actionDisconnect->setEnabled(b);
}

void MainWindow::on_actionDisconnect_triggered()
{
    db.close();
    qDebug() << "Disconnected!";
    enablingElements(false);
    enablingEditing(false);
}

void MainWindow::enablingEditing(bool b) {
    ui->actionAdd_row->setEnabled(b);
    ui->actionEdit_row->setEnabled(b);
    ui->actionDelete_row->setEnabled(b);
    ui->menuEditing->setEnabled(b);
}

void MainWindow::notSelected() {
    QMessageBox message;
    QMessageBox::StandardButton reply;
    reply = QMessageBox::critical(this,
                                  tr("Error"),
                                  tr("Selected row doesn't exist! Please, try again."),
                                  QMessageBox::Ok |
                                  QMessageBox::Cancel);

    message.setDefaultButton(QMessageBox::Ok);
    if(reply == QMessageBox::Ok) return;
    else return;
}

void MainWindow::on_actionEdit_row_triggered()
{
    dialogEdit select;
    int selected;
        while (true) {
            if (select.exec())
                selected = select.num();
            if (select.result() == dialogDelete::Rejected) return;
            if(verify(selected))
                break;
            else notSelected();
        }

     dialogRedaction edit;
     edit.editLabel(ui->comboBox->currentText());
     QString d1, d2, d3, d4, d5, d6, d7;

     while(true) {
         if(edit.exec())
             edit.getData(d1, d2, d3, d4, d5, d6, d7);
         if(edit.result() == dialogRedaction::Rejected)
             return;
         else
             break;
     }

     editing(d1, d2, d3, d4, d5, d6, d7, selected);
     on_buttonQuery_clicked();
}

void MainWindow::editing(QString d1, QString d2, QString d3, QString d4, QString d5, QString d6, QString d7, int number) {
    QSqlQuery query;
    QString tableName = ui->comboBox->currentText();
    QString queryValues;

    if (tableName == "clients") {
        queryValues = "full_name = '" + d1 + "', phone_number = '" + d2 + "'" + ", e_mail = '" + d3 + "'" + ", passport_data = '" + d4 + "'" + ", address = '" + d5 + "'";
    }
    else if (tableName == "clientsrequests") {
        queryValues = "id_client = " + d1 + ", type_immovable = '" + d2 + "', preferences = '" + d3 + "'";
    }
    else if (tableName == "deals") {
        queryValues = "id_client = " + d1 + ", id_employee = '" + d2 + "', id_immovable = '" + d3 + "'" + ", trans_date = '" + d4 + "'" + ", trans_amount = '" + d5 + "'" + ", deal_desc = '" + d6 + "'" + ", id_owner = '" + d7 + "'";

    }
    else if (tableName == "employees") {
        queryValues =  "full_name = '" + d1 + "'" + + ", job = '" + d2 + "', phone_number = '" + d3 + "', e_mail = '" + d4 + "', passport_data = '" + d5 + "'";
    }
    else if (tableName == "immovables") {
        queryValues = "id_type = '" + d1 + "', address = '" + d2 + "', parameters = '" + d3 + "', description = '" + d4  + "', id_owner = '" + d5 + "'";
    }
    else if (tableName == "immovablestypes") {
        queryValues = "name = '" + d1 + "'";
    }
    else if (tableName == "owners") {
        queryValues = "full_name = '" + d1 + "', address = '" + d2 + "', phone_number = '" + d3 + "', e_mail = '" + d4 + "', passport_data = " + d5 + "'";
    }
    else if (tableName == "ownersrequests") {
        queryValues = "id_owner = " + d1 + ", id_immovable = '" + d2 + "', preferences = " + d3 + "'";
    }

    query.exec("SELECT * FROM " + ui->comboBox->currentText());
    QString columnName = query.record().fieldName(0);
    query.exec("UPDATE " + ui->comboBox->currentText() + " SET " + queryValues + " WHERE " + columnName + " = " + QString::number(number));
}

void MainWindow::on_actionAdd_row_triggered()
{
    dialogRedaction add;
    add.editLabel(ui->comboBox->currentText());
    QString d1, d2, d3, d4, d5, d6, d7;

    while(true) {
        if(add.exec())
            add.getData(d1, d2, d3, d4, d5, d6, d7);
        if(add.result() == dialogRedaction::Rejected)
            return;
        else
            break;
    }

    adding(d1, d2, d3, d4, d5, d6, d7);
    on_buttonQuery_clicked();
}

void MainWindow::adding(QString d1, QString d2, QString d3, QString d4, QString d5, QString d6, QString d7) {
    QSqlQuery query;
    QString tableName = ui->comboBox->currentText();
    QString queryValues;
    QString queryColumns;

    if (tableName == "clients") {
        QSqlQuery rowCountQuery("SELECT COUNT(*) as num_rows FROM clients");
        rowCountQuery.next();
        queryValues = "('" + d1 + "','" + d2 + "','" + d3 + "','" + d4 + "','" + d5 + "')";
        queryColumns = "(full_name, phone_number, e_mail, passport_data, address)";
    }
    else if (tableName == "clientsrequests") {
        QSqlQuery rowCountQuery("SELECT COUNT(*) as num_rows FROM clientsrequests");
        rowCountQuery.next();
        queryValues = "(" + d1 + "', '" + d2 + "', '" + d3 + "', " + ")";
        queryColumns = "(id_client, type_immovable, preferences)";
    }
    else if (tableName == "deals") {
        QSqlQuery rowCountQuery("SELECT COUNT(*) as num_rows FROM deals");
        rowCountQuery.next();
        queryValues = "('" + d1 + "'," + d2 + "',"+ d3 + "'," + d4 + "'," + d5 + "'," + d6 + "'," + d7 + "')";
        queryColumns = "(id_client, id_employee, id_immovable, trans_date, trans_amount, deal_desc, id_owner)";
    }
    else if (tableName == "employees") {
        QSqlQuery rowCountQuery("SELECT COUNT(*) as num_rows FROM employees");
        rowCountQuery.next();
        queryValues = "('" + d1 + "'," + d2 + "'," + d3 + "'," + d4 + "'," + d5 + "')";
        queryColumns = "(full_name,job,phone_number,e_mail,passport_data)";
    }
    else if (tableName == "immovables") {
        QSqlQuery rowCountQuery("SELECT COUNT(*) as num_rows FROM immovables");
        rowCountQuery.next();
        queryValues = "('" + d1 + "',"+ d2 + "',"+ d3 + "'," + d4 + "'," + d5 + "')";
        queryColumns = "(id_type, address, parameters, description, id_owner)";
    }
    else if (tableName == "immovablestypes") {
        QSqlQuery rowCountQuery("SELECT COUNT(*) as num_rows FROM immovablestypes");
        rowCountQuery.next();
        queryValues = "('" + d1 + "')";
        queryColumns = "(name)";
    }
    else if (tableName == "owners") {
        QSqlQuery rowCountQuery("SELECT COUNT(*) as num_rows FROM train");
        rowCountQuery.next();
        queryValues = "('" + d1 + "'," + d2 + "'," + d3 + "'," + d4 + "'," + d5 + ")";
        queryColumns = "(full_name, address, phone_number, e_mail, passport_data)";
    }
    else if (tableName == "ownersrequests") {
        QSqlQuery rowCountQuery("SELECT COUNT(*) as num_rows FROM wagontype");
        rowCountQuery.next();
        queryValues = "('" + d1 + "'," + d2 + "'," + d3 + ")";
        queryColumns = "(id_owner, id_immovable, preferences)";
    }

    bool result = query.exec("INSERT INTO " + ui->comboBox->currentText() + " " + queryColumns +  " VALUES " + queryValues);
    qDebug()<<"INSERT INTO " + ui->comboBox->currentText() + queryColumns + " VALUES " + queryValues<<endl;

    if(!result){
        QMessageBox::information(this, tr("Error"), query.lastError().text());
        return;}
    else
        QMessageBox::information(this, tr("Adding successfull!"), tr("Adding of line was successful."));
}

void MainWindow::on_actionDelete_row_triggered()
{
    dialogDelete select;
    int selected;
    while (true) {
        if (select.exec())
            selected = select.num();
        if (select.result() == dialogDelete::Rejected) return;
        if(verify(selected))
            break;
        else notSelected();
    }
    deleting(selected);
    on_buttonQuery_clicked();
}

bool MainWindow::verify(int ver) {
    QSqlQuery query;
    query.exec("SELECT * FROM " + ui->comboBox->currentText());
    while (query.next())
        if (ver == query.value(0))
            return true;
    return false;
}

void MainWindow::deleting(int del) {
    QSqlQuery query;
    QString string_del = QString::number(del);
    query.exec("SELECT * FROM " + ui->comboBox->currentText());
    QString columnDel = query.record().fieldName(0);
    qDebug()<< "DELETE FROM " + ui->comboBox->currentText() + " WHERE " + columnDel + " = " + string_del << Qt::endl;
    bool success = query.exec("DELETE FROM " + ui->comboBox->currentText() + " WHERE " + columnDel + " = " + string_del);
    if (!success){
        qCritical() << "An error occurred during deleting record: " << query.lastError().text();
    }
    query.exec("UPDATE " + ui->comboBox->currentText() + " SET " + columnDel + " = " + columnDel + " - 1  WHERE " + columnDel + " > " + string_del);
    if (!query.isActive())
    {
        qCritical() << "An error occurred during reindexing: " << query.lastError().text();
    }
}

void MainWindow::on_actionAbout_the_author_triggered()
{
    dialogAuthor Add;
    Add.exec();
    if(Add.result() == dialogAuthor::Rejected)
        return;
}

// Создание меню с выбором языков
void MainWindow::createLanguageMenu()
{
    languageActionGroup = new QActionGroup(this);
    connect(languageActionGroup, &QActionGroup::triggered, this, &MainWindow::switchLanguage);
    QDir dir(qmPath);
    QStringList fileNames = dir.entryList(QStringList("cw-realtor_*.qm"));
    qDebug() << fileNames;
    for (int i = 0; i < fileNames.size(); i++)
    {
        QString locale = fileNames[i];
        locale.remove(0, locale.indexOf('_') + 1);
        locale.truncate(locale.lastIndexOf('.'));
        QTranslator translator;
        translator.load(fileNames[i], qmPath);
        QString language = translator.translate("MainWindow", "English");
        QAction *action = new QAction(tr("%2").arg(language), this);
        action->setCheckable(true);
        action->setData(locale);
        ui->menuLanguage->addAction(action);
        languageActionGroup->addAction(action);
        if (language == "English")
            action->setChecked(true);
    }
}

void MainWindow::switchLanguage(QAction *action)
{
    QString locale = action->data().toString();
    appTranslator.load("cw-realtor_" + locale + ".qm", qmPath);
    locale.chop(3);
    qtTranslator.load("qt_" + locale, QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    ui->retranslateUi(this);
    setWindowTitle(tr("cw-realtor"));
}

void MainWindow::on_buttonQuery_clicked()
{

    QSqlQuery query(db);
    model->clear();
    QStringList horizontalHeader; // столбцы
    QStringList verticalHeader; // строки

    enablingEditing(true);
    if (ui->comboBox->currentText() == "clients") { // для таблицы с отделам

        query.exec("SELECT * FROM clients ORDER BY id ASC");

        horizontalHeader << tr("id") << tr("Full Name") << tr("Phone number") << tr("e-mail")<< tr("Passport data")<< tr("Address");
        for(int i = 0; i < horizontalHeader.size(); ++i) {model->setHeaderData(i, Qt::Horizontal, horizontalHeader[i]);}

        while (query.next())
            verticalHeader.append(query.value(0).toString());

        query.seek(-1);

        model->setQuery(query);


    }

    else if (ui->comboBox->currentText() == "clientsrequests") { // для таблицы с клиентами

        query.exec("SELECT * FROM clientsrequests ORDER BY id ASC");

        horizontalHeader << tr("id") << tr("id Client") << tr("Immovable type")<< tr("Preferences");
        for(int i = 0; i < horizontalHeader.size(); ++i) {model->setHeaderData(i, Qt::Horizontal, horizontalHeader[i]);}

        while (query.next())
            verticalHeader.append(query.value(0).toString());

        query.seek(-1);

        model->setQuery(query);
    }

    else if (ui->comboBox->currentText() == "deals") {

        query.exec("SELECT * from deals \
                   ORDER BY id ASC");

        horizontalHeader << tr("id") << tr("id Client") << tr("id Employee") << tr("id Immovable") << tr("Transfer date") << tr("Amount") << tr("Deal description") << tr("id Owner");
        for(int i = 0; i < horizontalHeader.size(); ++i) {model->setHeaderData(i, Qt::Horizontal, horizontalHeader[i]);}

        while (query.next())
            verticalHeader.append(query.value(0).toString());

        query.seek(-1);

        model->setQuery(query);
    }

    else if (ui->comboBox->currentText() == "employees") {

        query.exec("SELECT * FROM employees ORDER BY id ASC");


        horizontalHeader << tr("id") << tr("Full name") << tr("Job") << tr("Phone number") << tr("e-mail") << tr("Passport data");
        for(int i = 0; i < horizontalHeader.size(); ++i) {model->setHeaderData(i, Qt::Horizontal, horizontalHeader[i]);}

        while (query.next())
            verticalHeader.append(query.value(0).toString());

        query.seek(-1);

        model->setQuery(query);
    }

    else if (ui->comboBox->currentText() == "immovables") {

        query.exec("SELECT * FROM immovables \
                    ORDER BY id ASC");

        horizontalHeader << tr("id") << tr("id type immovable") << tr("Address") << tr("Parameters") << tr("Description") << tr("id Owner");
        for(int i = 0; i < horizontalHeader.size(); ++i) {model->setHeaderData(i, Qt::Horizontal, horizontalHeader[i]);}

        while (query.next())
            verticalHeader.append(query.value(0).toString());

        query.seek(-1);

        model->setQuery(query);
    }

    else if (ui->comboBox->currentText() == "immovablestypes") {

        query.exec("SELECT * FROM immovablestypes ORDER BY id ASC");

        horizontalHeader << tr("id") << tr("Name");
        for(int i = 0; i < horizontalHeader.size(); ++i) {model->setHeaderData(i, Qt::Horizontal, horizontalHeader[i]);}

        while (query.next())
            verticalHeader.append(query.value(0).toString());

        query.seek(-1);

        model->setQuery(query);
    }

    else if (ui->comboBox->currentText() == "owners") {

        query.exec("SELECT * from owners ORDER BY id ASC");

        horizontalHeader << tr("id") << tr("Full Name") << tr("Address") << tr("Phone number") << tr("e-mail") << tr("Passport data");
        for(int i = 0; i < horizontalHeader.size(); ++i) {model->setHeaderData(i, Qt::Horizontal, horizontalHeader[i]);}

        while (query.next())
            verticalHeader.append(query.value(0).toString());

        query.seek(-1);

        model->setQuery(query);
    }

    else if (ui->comboBox->currentText() == "ownersrequests") {

        query.exec("SELECT * from ownersrequests ORDER BY id ASC");

        horizontalHeader << tr("id") << tr("id Owner") << tr("id Immovable") << tr("Preferences");
        for(int i = 0; i < horizontalHeader.size(); ++i) {model->setHeaderData(i, Qt::Horizontal, horizontalHeader[i]);}
        while (query.next())
            verticalHeader.append(query.value(0).toString());

        query.seek(-1);

        model->setQuery(query);
    }


    // передача данных в модель
    ui->tableView->setModel(model);
    ui->tableView->resizeRowsToContents();
    ui->tableView->resizeColumnsToContents();
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    //заполнение combobox названием столбцов
    ui->comboBoxSearch->clear();

    QSqlQueryModel *modelColumns = new QSqlQueryModel();
    modelColumns->setQuery("select column_name from information_schema.columns where table_catalog='realtor' \
                    and table_schema='public' and table_name='" + ui->comboBox->currentText() + "'");
    ui->comboBoxSearch->setModel(modelColumns);
    ui->comboBoxSearch->setModelColumn(0);
}

void MainWindow::on_pushButtonSearch_clicked()
{
    QString columnName = ui->comboBoxSearch->currentText();
    QSqlQuery query;
    model->clear();
    QStringList horizontalHeader; // столбцы
    QStringList verticalHeader; // строки
    enablingEditing(true);
    query.exec("SELECT * FROM " + ui->comboBox->currentText() + " WHERE CAST(" + columnName + " as text) like '%" + ui->lineEditSearch->text() + "%'");

    if (ui->comboBox->currentText() == "clients")
        horizontalHeader << tr("id") << tr("Full Name") << tr("Phone number") << tr("e-mail")<< tr("Passport data")<< tr("Address");
    if (ui->comboBox->currentText() == "clientsrequests") // для таблицы с клиентами
        horizontalHeader << tr("id") << tr("id Client") << tr("Immovable type")<< tr("Preferences");
    if (ui->comboBox->currentText() == "deals")
        horizontalHeader << tr("id") << tr("id Client") << tr("id Employee") << tr("id Immovable") << tr("Transfer date") << tr("Amount") << tr("Deal description") << tr("id Owner");
    if (ui->comboBox->currentText() == "employees")
        horizontalHeader << tr("id") << tr("Full name") << tr("Job") << tr("Phone number") << tr("e-mail") << tr("Passport data");
    if (ui->comboBox->currentText() == "immovables")
        horizontalHeader << tr("id") << tr("id type immovable") << tr("Address") << tr("Parameters") << tr("Description") << tr("id Owner");
    if (ui->comboBox->currentText() == "immovablestypes")
        horizontalHeader << tr("id") << tr("Name");
    if (ui->comboBox->currentText() == "owners")
        horizontalHeader << tr("id") << tr("Full Name") << tr("Address") << tr("Phone number") << tr("e-mail") << tr("Passport data");
    if (ui->comboBox->currentText() == "ownersrequests")
        horizontalHeader << tr("id") << tr("id Owner") << tr("id Immovable") << tr("Preferences");

    for(int i = 0; i < horizontalHeader.size(); ++i) {
        model->setHeaderData(i, Qt::Horizontal, horizontalHeader[i]);
    }

    while (query.next())
        verticalHeader.append(query.value(0).toString());

    query.seek(-1);

    model->setQuery(query);
    ui->tableView->setModel(model);
    ui->tableView->resizeRowsToContents();
    ui->tableView->resizeColumnsToContents();
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void MainWindow::setupModel()
{
    QSqlTableModel *model = new QSqlTableModel(this);
    QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(model);
    ui->tableView->setModel(proxyModel);
    ui->tableView->setSortingEnabled(true);
}
