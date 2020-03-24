#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDate>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setDebugLabel();
    setDateLabel();
    initSensorIcons();
    initStatusIcons();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setDateLabel(){
    QLocale::setDefault(QLocale("en_US"));
    QDate currDate = QDate::currentDate();
    ui->dateLabel->setText(QLocale().toString(currDate));
}

void MainWindow::setDebugLabel(){
    ui->debugLabel->setText("test");
}

void MainWindow::initSensorIcons(){
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

void MainWindow::initStatusIcons(){
    ui->iconYellowAlert->setPixmap(
                QPixmap(QString::fromUtf8(":/img/alert.png"))
                .scaled(30, 30, Qt::KeepAspectRatio));
    ui->iconRedAlert->setPixmap(
                QPixmap(QString::fromUtf8(":/img/redAlert.png"))
                .scaled(30, 30, Qt::KeepAspectRatio));
}
