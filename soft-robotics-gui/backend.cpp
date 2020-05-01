#include "backend.h"

BackEnd::BackEnd(QObject *parent)
    : QAbstractItemModel(parent)
{
}

QVariant BackEnd::headerData(int section, Qt::Orientation orientation, int role) const
{
    // FIXME: Implement me!
}

QModelIndex BackEnd::index(int row, int column, const QModelIndex &parent) const
{
    // FIXME: Implement me!
}

QModelIndex BackEnd::parent(const QModelIndex &index) const
{
    // FIXME: Implement me!
}

int BackEnd::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;

    // FIXME: Implement me!
}

int BackEnd::columnCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;

    // FIXME: Implement me!
}

bool BackEnd::hasChildren(const QModelIndex &parent) const
{
    // FIXME: Implement me!
}

bool BackEnd::canFetchMore(const QModelIndex &parent) const
{
    // FIXME: Implement me!
    return false;
}

void BackEnd::fetchMore(const QModelIndex &parent)
{
    // FIXME: Implement me!
}

QVariant BackEnd::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    // FIXME: Implement me!
    return QVariant();
}
