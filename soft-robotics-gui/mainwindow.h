#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "calibrationwindow.h"
#include <QVector>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QStandardItemModel;
class SpinBoxDelegate;
class DoubleSpinBoxDelegate;
class ComboBoxDelegate;
class TimeEditDelegate;
class DateEditDelegate;

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

    void on_actionNew_triggered();

private:
    Ui::MainWindow *ui;
    CalibrationWindow *calibrWin;
    QStandardItemModel *mModel;
    SpinBoxDelegate *m_spinnerDelegate;
    DoubleSpinBoxDelegate *m_doubleSpinDelegate;
    ComboBoxDelegate *m_comboBoxDelegate;
    TimeEditDelegate *m_timeEditDelegate;
    DateEditDelegate *m_dateEditDelegate;
    QString getValueAt(int ix, int jx);
    QString patientMetadata;
    QStringList gaitMetricsTableHeader;
    qint32 getMonthsSinceStroke();
    QVector<int> columnsDelegateSpinner, columnsDelegateDoubleSpinner, columnsDelegateComboBox;

    void setDateLabel();
    void setDebugLabel();
    void initStatusIcons();
    void setButtonStyles();
    void initGaitMetricsTable();
    void setTimeSinceStroke();

    void showErrorMessage(QString msg = nullptr, int errorNum = 0);
};
#endif // MAINWINDOW_H
