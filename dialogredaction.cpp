#include "dialogredaction.h"
#include "ui_dialogredaction.h"

dialogRedaction::dialogRedaction(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialogRedaction)
{
    ui->setupUi(this);
    setWindowTitle(tr("Redaction"));
    setFixedSize(1118, 405);
}

dialogRedaction::~dialogRedaction()
{
    delete ui;
}

void dialogRedaction::on_pushButtonOk_clicked()
{
    accept();
}


void dialogRedaction::on_pushButtonCancel_clicked()
{
    this->reject();
}

void dialogRedaction::getData(QString& d1, QString& d2, QString& d3, QString& d4, QString& d5, QString& d6, QString& d7)
{
    d1 = ui->lineEdit1->text();
    d2 = ui->lineEdit2->text();
    d3 = ui->lineEdit3->text();
    d4 = ui->lineEdit4->text();
    d5 = ui->lineEdit5->text();
    d6 = ui->lineEdit6->text();
    d7 = ui->lineEdit7->text();
}

void dialogRedaction::editLabel(QString tableName)
{
    if (tableName == "clients")
    {
        ui->label1->setText(tr("Full name:"));
        ui->label2->setText(tr("phone number:"));
        ui->label3->setText(tr("e-mail"));
        ui->label4->setText(tr("Passport Data"));
        ui->label5->setText(tr("Address"));
        ui->label6->setText(tr(""));
        ui->label7->setText(tr(""));
        ui->lineEdit1->setEnabled(true);
        ui->lineEdit2->setEnabled(true);
        ui->lineEdit3->setEnabled(true);
        ui->lineEdit4->setEnabled(true);
        ui->lineEdit5->setEnabled(true);
        ui->lineEdit6->setEnabled(false);
        ui->lineEdit7->setEnabled(false);
    }

    else if (tableName == "clientsrequests")
    {
        ui->label1->setText(tr("id Client:"));
        ui->label2->setText(tr("Immovable type:"));
        ui->label3->setText(tr("Preferences:"));
        ui->label4->setText(tr(""));
        ui->label5->setText(tr(""));
        ui->label6->setText(tr(""));
        ui->label7->setText(tr(""));
        ui->lineEdit1->setEnabled(true);
        ui->lineEdit2->setEnabled(true);
        ui->lineEdit3->setEnabled(true);
        ui->lineEdit4->setEnabled(false);
        ui->lineEdit5->setEnabled(false);
        ui->lineEdit6->setEnabled(false);
        ui->lineEdit7->setEnabled(false);
    }

    else if (tableName == "deals")
    {
        ui->label1->setText(tr("id Client:"));
        ui->label2->setText(tr("id Employee:"));
        ui->label3->setText(tr("id Immovable:"));
        ui->label4->setText(tr("Transfer date:"));
        ui->label5->setText(tr("Amount:"));
        ui->label6->setText(tr("Deal description:"));
        ui->label7->setText(tr("id Owner"));
        ui->lineEdit1->setEnabled(true);
        ui->lineEdit2->setEnabled(true);
        ui->lineEdit3->setEnabled(true);
        ui->lineEdit4->setEnabled(true);
        ui->lineEdit5->setEnabled(true);
        ui->lineEdit6->setEnabled(true);
        ui->lineEdit7->setEnabled(true);
    }

    else if (tableName == "employees")
    {
        ui->label1->setText(tr("Full Name:"));
        ui->label2->setText(tr("Job:"));
        ui->label3->setText(tr("Phone Number:"));
        ui->label4->setText(tr("e-mail:"));
        ui->label5->setText(tr("Passport data:"));
        ui->label6->setText(tr(""));
        ui->label7->setText(tr(""));
        ui->lineEdit1->setEnabled(true);
        ui->lineEdit2->setEnabled(true);
        ui->lineEdit3->setEnabled(true);
        ui->lineEdit4->setEnabled(true);
        ui->lineEdit5->setEnabled(true);
        ui->lineEdit6->setEnabled(false);
        ui->lineEdit7->setEnabled(false);
    }

    else if (tableName == "immovables")
    {
        ui->label1->setText(tr("id Type:"));
        ui->label2->setText(tr("Address:"));
        ui->label3->setText(tr("Parameters:"));
        ui->label4->setText(tr("Description:"));
        ui->label5->setText(tr("id Owner"));
        ui->label6->setText(tr(""));
        ui->label7->setText(tr(""));
        ui->lineEdit1->setEnabled(true);
        ui->lineEdit2->setEnabled(true);
        ui->lineEdit3->setEnabled(true);
        ui->lineEdit4->setEnabled(true);
        ui->lineEdit5->setEnabled(true);
        ui->lineEdit6->setEnabled(false);
        ui->lineEdit7->setEnabled(false);
    }

    else if (tableName == "immovablestypes")
    {
        ui->label1->setText(tr("Name:"));
        ui->label2->setText(tr(""));
        ui->label3->setText(tr(""));
        ui->label4->setText(tr(""));
        ui->label5->setText(tr(""));
        ui->label6->setText(tr(""));
        ui->label7->setText(tr(""));
        ui->lineEdit1->setEnabled(true);
        ui->lineEdit2->setEnabled(false);
        ui->lineEdit3->setEnabled(false);
        ui->lineEdit4->setEnabled(false);
        ui->lineEdit5->setEnabled(false);
        ui->lineEdit6->setEnabled(false);
        ui->lineEdit7->setEnabled(false);
    }

    else if (tableName == "owners")
    {
        ui->label1->setText(tr("Full name:"));
        ui->label2->setText(tr("Address:"));
        ui->label3->setText(tr("Phone number:"));
        ui->label4->setText(tr("e-mail"));
        ui->label5->setText(tr("Passport data"));
        ui->label6->setText(tr(""));
        ui->label7->setText(tr(""));
        ui->lineEdit1->setEnabled(true);
        ui->lineEdit2->setEnabled(true);
        ui->lineEdit3->setEnabled(true);
        ui->lineEdit4->setEnabled(true);
        ui->lineEdit5->setEnabled(true);
        ui->lineEdit6->setEnabled(false);
        ui->lineEdit7->setEnabled(false);
    }

    else if (tableName == "ownersrequests")
    {
        ui->label1->setText(tr("id Owner:"));
        ui->label2->setText(tr("id Immovable:"));
        ui->label3->setText(tr("Preferences:"));
        ui->label4->setText(tr(""));
        ui->label5->setText(tr(""));
        ui->label6->setText(tr(""));
        ui->label7->setText(tr(""));
        ui->lineEdit1->setEnabled(true);
        ui->lineEdit2->setEnabled(true);
        ui->lineEdit3->setEnabled(true);
        ui->lineEdit4->setEnabled(false);
        ui->lineEdit5->setEnabled(false);
        ui->lineEdit6->setEnabled(false);
        ui->lineEdit7->setEnabled(false);
    }
}
