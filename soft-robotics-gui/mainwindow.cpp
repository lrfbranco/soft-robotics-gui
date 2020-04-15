#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDate>
#include <QDebug>
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QString>
#include <QThread>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setDebugLabel();
    setDateLabel();
    initStatusIcons();
//    setLabelRunningStopped()
    setButtonStyles();
    initGaitMetricsTable();
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


void MainWindow::initStatusIcons(){
    ui->iconYellowAlert->setPixmap(
                QPixmap(QString::fromUtf8(":/img/alert.png"))
                .scaled(30, 30, Qt::KeepAspectRatio));
    ui->iconRedAlert->setPixmap(
                QPixmap(QString::fromUtf8(":/img/redAlert.png"))
                .scaled(30, 30, Qt::KeepAspectRatio));
}

void MainWindow::setButtonStyles(){
//    ui->stopButton:keyPressEvent()
//    QPushButton:pressed {
//        background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1,   stop:0 rgba(60, 186, 162, 255), stop:1 rgba(98, 211, 162, 255))
//    }
//    QPushButton {
//         background-color: #3cbaa2; border: 1px solid black;
//         border-radius: 5px;
//    }

//    QPushButton:disabled {
//        background-color: rgb(170, 170, 127)
//    }
}

void MainWindow::initGaitMetricsTable(){
    QTableWidget* m_pTableWidget = ui->gaitMetricsTable;
    m_pTableWidget->setColumnCount(7);
    m_pTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QStringList  m_TableHeader;
    m_TableHeader <<"Date" << "10m\n(mm:ss)" << "6MWT\n(m)" << "Total\nDistance\n(m)"
                 << "Average\nSpeed\n(m\\s)" << "Disconfort\nLevel" << "Dificulty\nLevel";
    m_pTableWidget->setHorizontalHeaderLabels(m_TableHeader);
    m_pTableWidget->setWordWrap(true);
}













//void MainWindow::on_labelRunningStopped_objectNameChanged(const QString &objectName)
//{

//}

void MainWindow::on_calibrationButton_clicked()
{
    calibrWin = new CalibrationWindow(this);
    calibrWin->show();
}

void MainWindow::on_actionLoadPatient_triggered()
{
    QStringList fileName;
    const QStringList fileFilters = { "CSV Files (*.csv)" , "Text Files (*.txt)" };
    QFileDialog fileDialog(this);

    fileDialog.setFileMode(QFileDialog::ExistingFile);
    fileDialog.setViewMode(QFileDialog::Detail);
    fileDialog.setNameFilters(fileFilters);

    if (fileDialog.exec()) {
        fileName = fileDialog.selectedFiles();
    }

    if (fileName.isEmpty()) {
        showErrorMessage(0, fileName.first());
        return;
    }

    QFile file(fileName.first());

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        showErrorMessage(0, fileName.first());
        return;
    }



}

void MainWindow::showErrorMessage(int errorNum, QString msg){
    QMessageBox mBox;
    QString s;
    switch(errorNum){
        case 0:
            // Error opening file
            s = "Could not open file: \"" + msg + "\".";
            mBox.information(this, "Error", s);
        break;
        default:
            mBox.information(this, "Error", "An error has occurred.");
        break;
    }
}























