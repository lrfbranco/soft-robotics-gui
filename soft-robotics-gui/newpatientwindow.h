#ifndef NEWPATIENTWINDOW_H
#define NEWPATIENTWINDOW_H

#include <QDialog>

namespace Ui {
class NewPatientWindow;
}

class NewPatientWindow : public QDialog
{
    Q_OBJECT

public:
    explicit NewPatientWindow(QWidget *parent = nullptr);
    ~NewPatientWindow();

private:
    Ui::NewPatientWindow *ui;
};

#endif // NEWPATIENTWINDOW_H
