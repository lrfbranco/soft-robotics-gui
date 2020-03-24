#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDate>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCurrentDate();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setCurrentDate(){
    QLocale::setDefault(QLocale("en_US"));
    QDate currDate = QDate::currentDate();
    ui->dateLabel->setText(QLocale().toString(currDate));
}
