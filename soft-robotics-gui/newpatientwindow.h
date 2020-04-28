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
    QString getPatientName() const;
    QString getPhysicianName() const;
    QDate getBirthDate() const;
    QDate getStrokeDate() const;


private slots:
    void on_buttonBox_accepted();

    void on_lineEditName_textChanged(const QString &arg1);

    void on_lineEditPhysician_textChanged(const QString &arg1);

    void on_dateEditBirth_editingFinished();

    void on_dateEditStroke_editingFinished();

private:
    Ui::NewPatientWindow *ui;
    bool initialized;
    QVector<bool> requiredFields;

protected:
    virtual void showEvent(QShowEvent *event) override;

};

#endif // NEWPATIENTWINDOW_H
