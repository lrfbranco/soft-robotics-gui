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

class RealTimeWindow;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void gaitTableHeightChanged();

private slots:
    void on_calibrationButton_clicked();
    void on_actionLoadPatient_triggered();
    void on_actionSave_triggered();
    void on_actionNew_triggered();
    void on_startButton_clicked();
    void on_stopButton_clicked();
    void on_yellowAlert_setState(bool newState);
    void on_redAlert_setState(bool newState);
    void on_addMetricButton_clicked();
    void on_deleteMetricButton_clicked();
    void gaitTable_changeHeight();

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
    int tableHeaderHeight;
    QStringList m_TableHeader;

    RealTimeWindow *m_realTimeWindow;

    void setDateLabel();
    void setDebugLabel();
    void initStatusIcons();
    void setButtonStyles();
    void initGaitMetricsTable();
    void setTimeSinceStroke();
    void adjustMetadataSizes();

    void showErrorMessage(QString msg = nullptr, int errorNum = 0);
    void setupGaitTableHeader();
};
#endif // MAINWINDOW_H
