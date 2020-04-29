#include "timeeditdelegate.h"
#include <QTimeEdit>
#include <QDebug>

TimeEditDelegate::TimeEditDelegate(QObject *parent)
    : QItemDelegate(parent)
{

}

QWidget *TimeEditDelegate::createEditor(QWidget *parent,
                                        const QStyleOptionViewItem &option,
                                        const QModelIndex &index) const
{
    QTimeEdit *timeEdit = new QTimeEdit(parent);
    timeEdit->setTimeRange(QTime(0, 0), QTime(59, 59));
    timeEdit->setDisplayFormat("mm:ss");
    timeEdit->stepBy(1);

    (void) option;
    (void) index;
    return timeEdit;
}

void TimeEditDelegate::setEditorData(QWidget *editor,
                                     const QModelIndex &index) const
{
    QTimeEdit *timeEdit = static_cast<QTimeEdit *>(editor);
    timeEdit->setTime(index.data().toTime());
}

void TimeEditDelegate::setModelData(QWidget *editor,
                                    QAbstractItemModel *model,
                                    const QModelIndex &index) const
{
    QTimeEdit *timeEdit = static_cast<QTimeEdit *>(editor);
    model->setData(index, timeEdit->time().toString("mm:ss"));
}

void TimeEditDelegate::updateEditorGeometry(QWidget *editor,
                                            const QStyleOptionViewItem &option,
                                            const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
    (void) index;
}
