#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
//    void on_labelRunningStopped_objectNameChanged(const QString &objectName);

private:
    Ui::MainWindow *ui;
    void setDateLabel();
    void setDebugLabel();
    void initSensorIcons();
    void initStatusIcons();
    void setButtonStyles();
};
#endif // MAINWINDOW_H
