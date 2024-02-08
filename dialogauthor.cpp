#include "dialogauthor.h"
#include "ui_dialogauthor.h"

dialogAuthor::dialogAuthor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialogAuthor)
{
    ui->setupUi(this);
    setFixedSize(this->size());
    setWindowTitle(tr("Information about the program"));
    ui->label->setText(tr("The program is produced by the student of ICTMS-3-8\nSafin Ralif Rafisovich"));
}

dialogAuthor::~dialogAuthor()
{
    delete ui;
}

void dialogAuthor::on_pushButtonOk_clicked()
{
    this->reject();
}
