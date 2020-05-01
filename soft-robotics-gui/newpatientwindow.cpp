#include "newpatientwindow.h"
#include "ui_newpatientwindow.h"
#include <QPushButton>
#include <QShowEvent>
#include <QDebug>

NewPatientWindow::NewPatientWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewPatientWindow)
{
    ui->setupUi(this);
    initialized = false;
    requiredFields = {false, false, false, false};
    ui->lineEditName->setMaxLength(36);
    ui->lineEditPhysician->setMaxLength(36);
    ui->dateEditBirth->setMaximumDate( QDate::currentDate() );
    ui->dateEditStroke->setMaximumDate( QDate::currentDate() );
}

NewPatientWindow::~NewPatientWindow()
{
    delete ui;
}

QString NewPatientWindow::getPatientName() const
{
    return ui->lineEditName->text();
}

QString NewPatientWindow::getPhysicianName() const
{
    return ui->lineEditPhysician->text();
}

QDate NewPatientWindow::getBirthDate() const
{
    return ui->dateEditBirth->date();
}

QDate NewPatientWindow::getStrokeDate() const
{
    return ui->dateEditStroke->date();
}

void NewPatientWindow::on_buttonBox_accepted()
{

}

void NewPatientWindow::showEvent(QShowEvent *event)
{
    if(!initialized) {
        initialized = true;
        ui->buttonBox->button( QDialogButtonBox::Save )->setEnabled( false );
    }

    if (requiredFields.indexOf(false) == -1)
        ui->buttonBox->button( QDialogButtonBox::Save )->setEnabled( true );
    else
        ui->buttonBox->button( QDialogButtonBox::Save )->setEnabled( false );

//    qDebug() << requiredFields;
    QDialog::showEvent(event);
}

void NewPatientWindow::on_lineEditName_textChanged(const QString &arg1)
{
    if (arg1.isNull() || arg1.isEmpty()){
        requiredFields[0] = false;
    }
    else {
        requiredFields[0] = true;
    }
    showEvent(new QShowEvent());
}

void NewPatientWindow::on_lineEditPhysician_textChanged(const QString &arg1)
{
    if (arg1.isNull() || arg1.isEmpty()){
        requiredFields[1] = false;
    }
    else {
        requiredFields[1] = true;
    }
    showEvent(new QShowEvent());
}

void NewPatientWindow::on_dateEditBirth_editingFinished()
{
    requiredFields[2] = true;
    showEvent(new QShowEvent());
}

void NewPatientWindow::on_dateEditStroke_editingFinished()
{
    requiredFields[3] = true;
    showEvent(new QShowEvent());
}
