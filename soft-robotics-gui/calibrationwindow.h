#ifndef CALIBRATIONWINDOW_H
#define CALIBRATIONWINDOW_H

#include <QDialog>

namespace Ui {
class CalibrationWindow;
}

class CalibrationWindow : public QDialog
{
    Q_OBJECT

public:
    explicit CalibrationWindow(QWidget *parent = nullptr);
    ~CalibrationWindow();

private:
    Ui::CalibrationWindow *ui;
};

#endif // CALIBRATIONWINDOW_H
