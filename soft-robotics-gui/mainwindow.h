#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "calibrationwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QStandardItemModel;
class SpinBoxDelegate;
class DoubleSpinBoxDelegate;
class ComboBoxDelegate;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
//    void on_labelRunningStopped_objectNameChanged(const QString &objectName);

    void on_calibrationButton_clicked();

    void on_actionLoadPatient_triggered();

    void on_actionSave_triggered();

private:
    Ui::MainWindow *ui;
    CalibrationWindow *calibrWin;
    QStandardItemModel *mModel;
    SpinBoxDelegate *m_spinnerDelegate;
    DoubleSpinBoxDelegate *m_doubleSpinDelegate;
    ComboBoxDelegate *m_comboBoxDelegate;
    QString getValueAt(int ix, int jx);
    QString patientMetadata;
    QStringList gaitMetricsTableHeader;
    qint32 getMonthsSinceStroke();

    void setDateLabel();
    void setDebugLabel();
    void initStatusIcons();
    void setButtonStyles();
    void initGaitMetricsTable();

    void showErrorMessage(QString msg = nullptr, int errorNum = 0);
};
#endif // MAINWINDOW_H
