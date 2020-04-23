#include "doublespinboxdelegate.h"
#include <QDoubleSpinBox>
#include <QDebug>

DoubleSpinBoxDelegate::DoubleSpinBoxDelegate(QObject *parent) :
    QItemDelegate(parent)
{
    QLocale::setDefault(QLocale("en_US"));
}

QWidget *DoubleSpinBoxDelegate::createEditor(QWidget *parent,
                              const QStyleOptionViewItem &option,
                              const QModelIndex &index) const
{
    QDoubleSpinBox *spinner = new QDoubleSpinBox(parent);
    spinner->setMinimum(0);
    spinner->setMaximum(INT_MAX);
    spinner->setDecimals(2);
    spinner->setSingleStep(0.01);
    (void) option;
    (void) index;
    return spinner;
}
void DoubleSpinBoxDelegate::setEditorData(QWidget *editor,
                           const QModelIndex &index) const
{
    QDoubleSpinBox *spinner = static_cast<QDoubleSpinBox *>(editor);
    spinner->setValue(index.data().toInt());
}
void DoubleSpinBoxDelegate::setModelData(QWidget *editor,
                          QAbstractItemModel *model,
                          const QModelIndex &index) const
{
    QDoubleSpinBox *spinner = static_cast<QDoubleSpinBox *>(editor);
    model->setData(index, spinner->value());
    qDebug() << "spinner" << spinner;
    qDebug() << "ModelIdx" << index;
    qDebug() << "val: " << spinner->value();
}
void DoubleSpinBoxDelegate::updateEditorGeometry(QWidget *editor,
                                  const QStyleOptionViewItem &option,
                                  const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
    (void) index;
}
