#include "realtimewindow.h"
#include "ui_realtimewindow.h"

RealTimeWindow::RealTimeWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RealTimeWindow),
    mPlot(nullptr),
    mTag1(nullptr),
    mTag2(nullptr)
{
    ui->setupUi(this);

    mPlot = new QCustomPlot(this);
    setCentralWidget(mPlot);

    // configure plot to have two right axes:
    mPlot->yAxis->setTickLabels(false);
    connect(mPlot->yAxis2, SIGNAL(rangeChanged(QCPRange)), mPlot->yAxis, SLOT(setRange(QCPRange))); // left axis only mirrors inner right axis
    mPlot->yAxis2->setVisible(true);
    mPlot->axisRect()->addAxis(QCPAxis::atRight);
    mPlot->axisRect()->axis(QCPAxis::atRight, 0)->setPadding(30); // add some padding to have space for tags
    mPlot->axisRect()->axis(QCPAxis::atRight, 1)->setPadding(30); // add some padding to have space for tags


    // create graphs:
    mGraph1 = mPlot->addGraph(mPlot->xAxis, mPlot->axisRect()->axis(QCPAxis::atRight, 0));
    mGraph2 = mPlot->addGraph(mPlot->xAxis, mPlot->axisRect()->axis(QCPAxis::atRight, 1));
    mGraph1->setPen(QPen(QColor(250, 120, 0)));
    mGraph2->setPen(QPen(QColor(0, 180, 60)));

    // create tags with newly introduced AxisTag class (see axistag.h/.cpp):
    mTag1 = new AxisTag(mGraph1->valueAxis());
    mTag1->setPen(mGraph1->pen());
    mTag2 = new AxisTag(mGraph2->valueAxis());
    mTag2->setPen(mGraph2->pen());

    // add regions
    mPlot->yAxis->setRange(QCPRange(-1.5, 1.5));
//    mPlot->xAxis->setRange(QCPRange(-10, 10));

    QBrush lightRedBrush = QBrush(QColor(255,100,120, 60));
    QBrush lightYellowBrush = QBrush(QColor(255,240,100, 60));

    lowerRect = new QCPItemRect(mPlot);
    upperRect = new QCPItemRect(mPlot);

    lowerRect->setPen(Qt::NoPen);
    lowerRect->setBrush(lightRedBrush);
    upperRect->setPen(Qt::NoPen);
    upperRect->setBrush(lightYellowBrush);

    lowerBoundary = -0.5;
    upperBoundary = 0.8;
    lowerRect->topLeft->setCoords(QPointF(INT_MIN, lowerBoundary));
    lowerRect->bottomRight->setCoords(QPointF(INT_MAX, INT_MIN));
    upperRect->topLeft->setCoords(QPointF(INT_MIN, INT_MAX));
    upperRect->bottomRight->setCoords(QPointF(INT_MAX, upperBoundary));


    connect(&mDataTimer, SIGNAL(timeout()), this, SLOT(timerSlot()));
    mDataTimer.start(40);
}

RealTimeWindow::~RealTimeWindow()
{
    delete ui;
}

void RealTimeWindow::timerSlot()
{
  // calculate and add a new data point to each graph:
  mGraph1->addData(mGraph1->dataCount(), qSin(mGraph1->dataCount()/50.0)+qSin(mGraph1->dataCount()/50.0/0.3843)*0.25);
  mGraph2->addData(mGraph2->dataCount(), qCos(mGraph2->dataCount()/50.0)+qSin(mGraph2->dataCount()/50.0/0.4364)*0.15);

  // make key axis range scroll with the data:
  mPlot->xAxis->rescale();
  mGraph1->rescaleValueAxis(false, true);
  mGraph2->rescaleValueAxis(false, true);
  mPlot->xAxis->setRange(mPlot->xAxis->range().upper, 100, Qt::AlignRight);

  // update the vertical axis tag positions and texts to match the rightmost data point of the graphs:
  double graph1Value = mGraph1->dataMainValue(mGraph1->dataCount()-1);
  double graph2Value = mGraph2->dataMainValue(mGraph2->dataCount()-1);
  mTag1->updatePosition(graph1Value);
  mTag2->updatePosition(graph2Value);
  mTag1->setText(QString::number(graph1Value, 'f', 2));
  mTag2->setText(QString::number(graph2Value, 'f', 2));

  qreal ylim = 1.2;
  mPlot->yAxis->setRange(QCPRange(-ylim, ylim));
  mPlot->yAxis2->setRange(QCPRange(-ylim, ylim));
  mPlot->axisRect()->axis(QCPAxis::atRight, 0)->setRange(QCPRange(-ylim, ylim));
  mPlot->axisRect()->axis(QCPAxis::atRight, 1)->setRange(QCPRange(-ylim, ylim));

  mPlot->replot();
  checkAlerts();
}

void RealTimeWindow::checkAlerts()
{
    auto val1 = mGraph1->data()->at(mGraph1->dataCount()-1)->value;
    auto val2 = mGraph2->data()->at(mGraph2->dataCount()-1)->value;

    if (val1 > upperBoundary || val2 > upperBoundary)
        yellowAlertChanged(true);
    else
        yellowAlertChanged(false);

    if (val1 < lowerBoundary || val2 < lowerBoundary)
        redAlertChanged(true);
    else
        redAlertChanged(false);
}
