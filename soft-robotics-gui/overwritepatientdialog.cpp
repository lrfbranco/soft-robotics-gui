#include "overwritepatientdialog.h"
#include "ui_overwritepatientdialog.h"

OverwritePatientDialog::OverwritePatientDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OverwritePatientDialog)
{
    ui->setupUi(this);
}

OverwritePatientDialog::~OverwritePatientDialog()
{
    delete ui;
}
