#include "dialogedit.h"
#include "ui_dialogedit.h"

dialogEdit::dialogEdit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialogEdit)
{
    ui->setupUi(this);
    setWindowTitle(tr("Edit"));
    setFixedSize(688, 193);
}

dialogEdit::~dialogEdit()
{
    delete ui;
}

void dialogEdit::on_pushButtonOk_clicked()
{
    num();
    accept();
}


void dialogEdit::on_pushButtonCancel_clicked()
{
    this->reject();
}

int dialogEdit::num()
{
    return ui->lineEdit->text().toInt();
}
