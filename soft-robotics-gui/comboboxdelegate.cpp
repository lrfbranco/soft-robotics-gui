#include "comboboxdelegate.h"
#include <QComboBox>
#include <QDebug>

ComboBoxDelegate::ComboBoxDelegate(QObject *parent) :
    QItemDelegate(parent)
{

}

QWidget *ComboBoxDelegate::createEditor(QWidget *parent,
                              const QStyleOptionViewItem &option,
                              const QModelIndex &index) const
{
    QComboBox *comboBox = new QComboBox(parent);
    comboBox->addItem("LOW");
    comboBox->addItem("MED");
    comboBox->addItem("HIGH");
    (void) option;
    (void) index;
    return comboBox;
}
void ComboBoxDelegate::setEditorData(QWidget *editor,
                           const QModelIndex &index) const
{
    QComboBox *comboBox = static_cast<QComboBox *>(editor);
    comboBox->setCurrentIndex(index.data().toInt());
}
void ComboBoxDelegate::setModelData(QWidget *editor,
                          QAbstractItemModel *model,
                          const QModelIndex &index) const
{
    QComboBox *comboBox = static_cast<QComboBox *>(editor);

    qDebug() << "comboBox" << comboBox;
    qDebug() << "editor" << editor;
    qDebug() << "ModelIdx" << index;
    qDebug() << "Idx: " << comboBox->currentIndex();
    qDebug() << "ItemD: " << comboBox->itemData(comboBox->currentIndex());
    qDebug() << "ItemD2: " << comboBox->currentData();
    model->setData(index,
                   comboBox->itemData(comboBox->currentIndex()));

}
void ComboBoxDelegate::updateEditorGeometry(QWidget *editor,
                                  const QStyleOptionViewItem &option,
                                  const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
    (void) index;
}
