#include "dateeditdelegate.h"
#include <QDateEdit>

DateEditDelegate::DateEditDelegate(QObject *parent)
    : QItemDelegate(parent)
{

}

QWidget *DateEditDelegate::createEditor(QWidget *parent,
                                        const QStyleOptionViewItem &option,
                                        const QModelIndex &index) const
{
    QDateEdit *dateEdit = new QDateEdit(parent);
    dateEdit->setMinimumDate(QDate(1900,1,1));
    dateEdit->setMaximumDate(QDate::currentDate().addDays(1));
    dateEdit->setDisplayFormat("MM/dd/yyyy");
    dateEdit->setCalendarPopup(true);

    (void) option;
    (void) index;
    return dateEdit;
}

void DateEditDelegate::setEditorData(QWidget *editor,
                                     const QModelIndex &index) const
{
    QDateEdit *dateEdit = static_cast<QDateEdit *>(editor);
    dateEdit->setDate(QDate::fromString(index.data().toString(), "MM/dd/yyyy"));
}

void DateEditDelegate::setModelData(QWidget *editor,
                                    QAbstractItemModel *model,
                                    const QModelIndex &index) const
{
    QDateEdit *dateEdit = static_cast<QDateEdit *>(editor);
    model->setData(index, dateEdit->date().toString("MM/dd/yyyy"));
}

void DateEditDelegate::updateEditorGeometry(QWidget *editor,
                                            const QStyleOptionViewItem &option,
                                            const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
    (void) index;
}
