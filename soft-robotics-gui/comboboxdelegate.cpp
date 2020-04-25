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
    auto comboCurrentIdx = comboBox->findText(index.data().toString());
    comboBox->setCurrentIndex(comboCurrentIdx);
}
void ComboBoxDelegate::setModelData(QWidget *editor,
                          QAbstractItemModel *model,
                          const QModelIndex &index) const
{
    QComboBox *comboBox = static_cast<QComboBox *>(editor);
    model->setData(index, comboBox->currentText());

}
void ComboBoxDelegate::updateEditorGeometry(QWidget *editor,
                                  const QStyleOptionViewItem &option,
                                  const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
    (void) index;
}
