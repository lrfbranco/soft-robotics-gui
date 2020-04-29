#ifndef TIMEEDITDELEGATE_H
#define TIMEEDITDELEGATE_H

#include <QItemDelegate>

class TimeEditDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit TimeEditDelegate(QObject *parent = nullptr);
protected:
    virtual QWidget *createEditor(QWidget *parent,
                                  const QStyleOptionViewItem &option,
                                  const QModelIndex &index) const override;
    virtual void setEditorData(QWidget *editor,
                               const QModelIndex &index) const override;
    virtual void setModelData(QWidget *editor,
                              QAbstractItemModel *model,
                              const QModelIndex &index) const override;
    virtual void updateEditorGeometry(QWidget *editor,
                                      const QStyleOptionViewItem &option,
                                      const QModelIndex &index) const override;

};


#endif // TIMEEDITDELEGATE_H
