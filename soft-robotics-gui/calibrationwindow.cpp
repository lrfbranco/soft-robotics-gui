#include "calibrationwindow.h"
#include "ui_calibrationwindow.h"

CalibrationWindow::CalibrationWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CalibrationWindow)
{
    ui->setupUi(this);
    initSensorIcons();
}

CalibrationWindow::~CalibrationWindow()
{
    delete ui;
}

void CalibrationWindow::initSensorIcons(){
    //    int h = ui->sensIconLeftThigh->height();
    //    int w = h; // Square icons
    ui->iconSensorLeftThigh->setPixmap(
                QPixmap(QString::fromUtf8(":/img/graySignal.png"))
                .scaled(25, 25, Qt::KeepAspectRatio));
    ui->iconSensorLeftShin->setPixmap(
                QPixmap(QString::fromUtf8(":/img/graySignal.png"))
                .scaled(25, 25, Qt::KeepAspectRatio));
    ui->iconSensorLeftFoot->setPixmap(
                QPixmap(QString::fromUtf8(":/img/graySignal.png"))
                .scaled(25, 25, Qt::KeepAspectRatio));
    ui->iconSensorRightThigh->setPixmap(
                QPixmap(QString::fromUtf8(":/img/greenSignal.png"))
                .scaled(25, 25, Qt::KeepAspectRatio));
    ui->iconSensorRightShin->setPixmap(
                QPixmap(QString::fromUtf8(":/img/yellowSignal.png"))
                .scaled(25, 25, Qt::KeepAspectRatio));
    ui->iconSensorRightFoot->setPixmap(
                QPixmap(QString::fromUtf8(":/img/redSignal.png"))
                .scaled(25, 25, Qt::KeepAspectRatio));
}
