#include "dialogdelete.h"
#include "ui_dialogdelete.h"

dialogDelete::dialogDelete(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialogDelete)
{
    ui->setupUi(this);
    setWindowTitle(tr("Delete"));
    setFixedSize(756, 183);
}

dialogDelete::~dialogDelete()
{
    delete ui;
}

void dialogDelete::on_pushButtonOk_clicked()
{
    num();
    accept();
}


void dialogDelete::on_pushButtonCancel_clicked()
{
    this->reject();
}

int dialogDelete::num()
{
    return ui->lineEdit->text().toInt();
}

