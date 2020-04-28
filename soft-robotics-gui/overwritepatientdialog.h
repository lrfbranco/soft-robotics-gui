#ifndef OVERWRITEPATIENTDIALOG_H
#define OVERWRITEPATIENTDIALOG_H

#include <QDialog>

namespace Ui {
class OverwritePatientDialog;
}

class OverwritePatientDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OverwritePatientDialog(QWidget *parent = nullptr);
    ~OverwritePatientDialog();

private:
    Ui::OverwritePatientDialog *ui;
};

#endif // OVERWRITEPATIENTDIALOG_H
