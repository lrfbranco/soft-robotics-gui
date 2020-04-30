#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDate>
#include <QDebug>
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QString>
#include <QThread>

#include <newpatientwindow.h>
#include <overwritepatientdialog.h>

#include <QStandardItemModel>
#include <QTextStream>
#include <spinboxdelegate.h>
#include <doublespinboxdelegate.h>
#include <comboboxdelegate.h>
#include <timeeditdelegate.h>
#include <dateeditdelegate.h>
#include <QSpinBox>

#include <realtimewindow.h>

#define GAIT_METRICS_TABLE_ROW_HEIGHT 30

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setDebugLabel();
    setDateLabel();
    initStatusIcons();
    setButtonStyles();
    initGaitMetricsTable();

    mModel = new QStandardItemModel(this);
    ui->gaitMetricsTableView->setModel(mModel);

    m_timeEditDelegate = new TimeEditDelegate(this);
    m_spinnerDelegate = new SpinBoxDelegate(this);
    m_doubleSpinDelegate = new DoubleSpinBoxDelegate(this);
    m_comboBoxDelegate = new ComboBoxDelegate(this);
    m_dateEditDelegate = new DateEditDelegate(this);

    ui->gaitMetricsTableView->setItemDelegateForColumn(0, m_dateEditDelegate);
    ui->gaitMetricsTableView->setItemDelegateForColumn(1, m_timeEditDelegate);
    ui->gaitMetricsTableView->setItemDelegateForColumn(2, m_spinnerDelegate);
    ui->gaitMetricsTableView->setItemDelegateForColumn(3, m_spinnerDelegate);
    ui->gaitMetricsTableView->setItemDelegateForColumn(4, m_doubleSpinDelegate);
    ui->gaitMetricsTableView->setItemDelegateForColumn(5, m_comboBoxDelegate);
    ui->gaitMetricsTableView->setItemDelegateForColumn(6, m_comboBoxDelegate);

    setupGaitTableHeader();
//    ui->gaitMetricsTableView->setSize);

    connect(this, SIGNAL(gaitTableHeightChanged()), this, SLOT(gaitTable_changeHeight()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupGaitTableHeader()
{
    m_TableHeader.clear();
    m_TableHeader <<"Date" << "10m\n(mm:ss)" << "6MWT\n(m)" << "Total\nDistance\n(m)"
                    << "Average\nSpeed\n(m\\s)" << "Disconfort\nLevel" << "Dificulty\nLevel";
    mModel->setHorizontalHeaderLabels(m_TableHeader);
    ui->gaitMetricsTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->gaitMetricsTableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->gaitMetricsTableView->horizontalHeader()->setStyleSheet("font-weight: bold;");
    mModel->setColumnCount(m_TableHeader.size());
    tableHeaderHeight = ui->gaitMetricsTableView->horizontalHeader()->sizeHint().height() + 1;
    ui->gaitMetricsTableView->setMinimumHeight(tableHeaderHeight);
    gaitTable_changeHeight();
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
//    QTableWidget* m_pTableWidget = ui->gaitMetricsTable;
//    m_pTableWidget->setColumnCount(7);
//    m_pTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

//    QStringList  m_TableHeader;
//    m_TableHeader <<"Date" << "10m\n(mm:ss)" << "6MWT\n(m)" << "Total\nDistance\n(m)"
//                 << "Average\nSpeed\n(m\\s)" << "Disconfort\nLevel" << "Dificulty\nLevel";
//    m_pTableWidget->setHorizontalHeaderLabels(m_TableHeader);
    //    m_pTableWidget->setWordWrap(true);
}

void MainWindow::setTimeSinceStroke()
{
    ui->timeSinceStroke->setText(QString("(%1 months ago)").arg(getMonthsSinceStroke()));
}

void MainWindow::on_calibrationButton_clicked()
{
    calibrWin = new CalibrationWindow(this);
    calibrWin->show();
}

void MainWindow::on_actionLoadPatient_triggered()
{
    if (patientMetadata != nullptr){
        OverwritePatientDialog opDialog(this);
        if(opDialog.exec() == QDialog::Rejected)
            return;
    }

    QFileDialog fileDialog(this);
    fileDialog.setFileMode(QFileDialog::ExistingFile);
    fileDialog.setViewMode(QFileDialog::Detail);
    const QStringList fileFilters = { "CSV Files (*.csv)" , "Text Files (*.txt)" };
    fileDialog.setNameFilters(fileFilters);

    QStringList fileName;
    if (fileDialog.exec()) {
        fileName = fileDialog.selectedFiles();
    }

    if (fileName.isEmpty()) {
//        showErrorMessage();
        return;
    }

    QFile file(fileName.first());

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        showErrorMessage(fileName.first(), 1);
        return;
    }

    QTextStream xin(&file);
    // Read first line with metadata and header:
    auto currLine = xin.readLine();
    auto cellsOnCurrLine = currLine.split(",");
    patientMetadata = cellsOnCurrLine.takeFirst(); // Remove first for metadata
    gaitMetricsTableHeader = cellsOnCurrLine; // The rest is header

    auto metadata = patientMetadata.split("#");
    ui->patientNameValue->setText(metadata.at(0).split(":").at(1));
    ui->physicianNameValue->setText(metadata.at(1).split(":").at(1));
    ui->strokeDateValue->setText(metadata.at(2).split(":").at(1));
    ui->birthDateValue->setText(metadata.at(3).split(":").at(1));

    setTimeSinceStroke();

    const int colCount = gaitMetricsTableHeader.size();
    mModel->setColumnCount(colCount);

    // Read rest of file
    int ix = 0;
    while (!xin.atEnd()) {
        mModel->setRowCount(ix); // Update nRows of table
        currLine = xin.readLine();
        auto cellsOnCurrLine = currLine.split(",");
        cellsOnCurrLine.takeFirst(); // Remove first element of all lines because of metadata

//        mModel->dele
        for (int jx = 0; jx < colCount; ++jx) {
            QStandardItem *item = new QStandardItem(cellsOnCurrLine.at(jx));
            item->setSizeHint(QSize(25, GAIT_METRICS_TABLE_ROW_HEIGHT));
            mModel->setItem(ix, jx, item);
        }
        ++ix;
    }
    file.close();
    gaitTable_changeHeight();
}

void MainWindow::on_actionSave_triggered()
{
    if (patientMetadata == nullptr){
        showErrorMessage("Please insert a New patient or Load an existing one", 0);
        return;
    }
    auto filename = QFileDialog::getSaveFileName(this,
        "Save", QDir::rootPath(), "CSV File (*.csv)");
    if (filename.isEmpty()){
        return;
    }
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        return;
    }
    QTextStream xout(&file);
    const int rowCount = mModel->rowCount();
    const int colCount = mModel->columnCount();

    // Save first line with format: metadata, headers
    xout << patientMetadata;
    foreach (const QString &header, gaitMetricsTableHeader) {
        xout << "," << header;
    }
    xout << "\n";

    // Save table values with index in first column (placeholder for metadata)
    for (int ix = 0; ix < rowCount; ++ix){
        xout << ix + 1 << "," << getValueAt(ix, 0);
        for (int jx = 1; jx < colCount; ++jx){
            xout << "," << getValueAt(ix, jx);
        }
        xout << "\n";
    }
    file.flush();
    file.close();

}

QString MainWindow::getValueAt(int ix, int jx)
{
    if (!mModel->item(ix, jx)) {
        return "";
    }
    return mModel->item(ix, jx)->text();
}

qint32 MainWindow::getMonthsSinceStroke()
{
    QLocale::setDefault(QLocale("en_US"));
    QDate currentDate = QDate::currentDate();

    QDate strokeDate = QDate::fromString(
                ui->strokeDateValue->text(),
                "MM/dd/yyyy");

    auto daysSinceStroke = strokeDate.daysTo(currentDate);

    return (qint32) daysSinceStroke / 30;
}

void MainWindow::showErrorMessage(QString msg, int errorNum){
    QMessageBox mBox;
    QString s;
    switch(errorNum){
        case 0:
            // Generic error message
            s = "An error has occurred. Data:\n\"" + msg + "\".";
            mBox.information(this, "Error", s);
        break;
        case 1:
            // Error opening file
            s = "Could not open file: \"" + msg + "\".";
            mBox.information(this, "Error", s);
        break;
        default:
            // Generic error without message
            mBox.information(this, "Error", "An error has occurred.");
        break;
    }
}

void MainWindow::on_actionNew_triggered()
{
    if (patientMetadata != nullptr){
        OverwritePatientDialog opDialog(this);
        if(opDialog.exec() == QDialog::Rejected)
            return;
    }

    NewPatientWindow npw(this);
    if (npw.exec() == QDialog::Rejected)
        return;

    ui->patientNameValue->setText(npw.getPatientName());
    ui->physicianNameValue->setText(npw.getPhysicianName());
    ui->birthDateValue->setText(npw.getBirthDate().toString("MM/dd/yyyy"));
    ui->strokeDateValue->setText(npw.getStrokeDate().toString("MM/dd/yyyy"));

    setTimeSinceStroke();

    // Reconstruct metadata:
    patientMetadata.clear();
    QTextStream ts(&patientMetadata);
    ts << "Name:" << ui->patientNameValue->text() << "#";
    ts << "Physician:" << ui->physicianNameValue->text() << "#";
    ts << "StrokeDate:" << ui->strokeDateValue->text() << "#";
    ts << "BirthDate:" << ui->birthDateValue->text() << "#";
    ts << "Created on:" << QDate::currentDate().toString("MM/dd/yyyy");

    // Recreate rest of header:
    gaitMetricsTableHeader.clear();
    gaitMetricsTableHeader << "Date"
                           << "10m (mm:ss)"
                           << "6MWT (m)"
                           << "Total Distance (m)"
                           << "Average Speed (m/s)"
                           << "Disconfort Level"
                           << "Difficulty Level";
//    mModel->clear();
//    setupGaitTableHeader();

//    qDebug() << gaitMetricsTableHeader;

//    auto metadata = patientMetadata.split("#");
//    qDebug() << npw.getPatientName();
//    qDebug() << npw.getPhysicianName();
//    qDebug() << npw.getBirthDate();
//    qDebug() << npw.getStrokeDate();
}

void MainWindow::on_startButton_clicked()
{
    if (m_realTimeWindow != nullptr)
        return;

    ui->labelRunningStopped->setText("Running");
    ui->iconRedAlert->setVisible(false);
    ui->iconYellowAlert->setVisible(false);

    m_realTimeWindow = new RealTimeWindow(this);
    m_realTimeWindow->setAttribute(Qt::WA_DeleteOnClose, true);
    connect(m_realTimeWindow, SIGNAL(destroyed()), this, SLOT(on_stopButton_clicked()));
    connect(m_realTimeWindow, SIGNAL(yellowAlertChanged(bool)), this, SLOT(on_yellowAlert_setState(bool)));
    connect(m_realTimeWindow, SIGNAL(redAlertChanged(bool)), this, SLOT(on_redAlert_setState(bool)));

    m_realTimeWindow->show();
}

void MainWindow::on_stopButton_clicked()
{
    if (m_realTimeWindow == nullptr)
        return;

    ui->labelRunningStopped->setText("Stopped");
    ui->iconRedAlert->setVisible(true);
    ui->iconYellowAlert->setVisible(true);
    ui->startButton->setFlat(false);
    m_realTimeWindow->close();
    m_realTimeWindow = nullptr;
}

void MainWindow::on_yellowAlert_setState(bool newState)
{
    if( ui->iconYellowAlert->isVisible() == newState)
        return;

    ui->iconYellowAlert->setVisible(newState);
}

void MainWindow::on_redAlert_setState(bool newState)
{
    if( ui->iconRedAlert->isVisible() == newState )
        return;

    ui->iconRedAlert->setVisible(newState);
}

void MainWindow::on_addMetricButton_clicked()
{
    int rowCount = mModel->rowCount() +1;// Update nRows of table
    mModel->setRowCount(rowCount);

    for (int j = 0; j < mModel->columnCount(); j++){
        QStandardItem *item = new QStandardItem("...");
        item->setSizeHint(QSize(25, GAIT_METRICS_TABLE_ROW_HEIGHT));
        mModel->setItem(rowCount-1, j, item);
    }
    gaitTableHeightChanged();
}

void MainWindow::on_deleteMetricButton_clicked()
{
    int rowCount = mModel->rowCount();
    if (rowCount == 0)
        return;

    rowCount--;    // Update nRows of table
    mModel->setRowCount(rowCount);
    gaitTableHeightChanged();
}

void MainWindow::gaitTable_changeHeight()
{
    qreal rowCount = mModel->rowCount();
    if (rowCount > 4)
        rowCount = 4.5;
    int newSize = tableHeaderHeight +
            GAIT_METRICS_TABLE_ROW_HEIGHT * rowCount + 1.4*rowCount;
    ui->gaitMetricsTableView->setMinimumHeight( newSize );
    ui->gaitMetricsTableView->setMaximumHeight( newSize );
    ui->gaitMetricsTableView->resizeRowsToContents();
}
