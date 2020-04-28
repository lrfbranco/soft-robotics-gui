#include "newpatientwindow.h"
#include "ui_newpatientwindow.h"

NewPatientWindow::NewPatientWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewPatientWindow)
{
    ui->setupUi(this);
}

NewPatientWindow::~NewPatientWindow()
{
    delete ui;
}
