#ifndef REALTIMEWINDOW_H
#define REALTIMEWINDOW_H

#include <QMainWindow>
#include "qcustomplot.h"
#include "axistag.h"

namespace Ui {
class RealTimeWindow;
}

class RealTimeWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit RealTimeWindow(QWidget *parent = nullptr);
    ~RealTimeWindow();

private slots:
  void timerSlot();

private:
    Ui::RealTimeWindow *ui;
    QCustomPlot *mPlot;
    QPointer<QCPGraph> mGraph1;
    QPointer<QCPGraph> mGraph2;
    AxisTag *mTag1;
    AxisTag *mTag2;
    QTimer mDataTimer;

    QCPItemRect *lowerRect;
    QCPItemRect *upperRect;
};

#endif // REALTIMEWINDOW_H
