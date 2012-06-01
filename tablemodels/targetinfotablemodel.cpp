#include "targetinfotablemodel.h"
#include "../model/State.h"
#include <QDebug>

TargetInfoTableModel::TargetInfoTableModel(SingleTarget *t, QObject *parent) :
    QAbstractTableModel(parent), target(t), timer(this)
{
    connect(&timer, SIGNAL(timeout()), this, SLOT(updateTable()));
    timer.start(300);
}

void TargetInfoTableModel::updateTable()
{
    if (!isTracking) {
        target = NULL;
        timer.stop();
    }

    //beginInsertRows(QModelIndex(), target->getStateCount(), target->getStateCount());
    reset();    // 跟新数据，使table和model同步
    emit dataChanged(this->index(0, 0), this->index(rowCount(QModelIndex()), columnCount(QModelIndex())));
    //endInsertRows();
}

int TargetInfoTableModel::rowCount(const QModelIndex &parent) const
{
    if (target == NULL) return 0;
    return target->getStateCount();
}

int TargetInfoTableModel::columnCount(const QModelIndex &parent) const
{
    return 11;
}

QVariant TargetInfoTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) return QVariant();
    if (role == Qt::TextAlignmentRole) {
        return int(Qt::AlignCenter | Qt::AlignVCenter);
    } else if (role == Qt::DisplayRole) {
        State *s = target->getState(index.row());
        switch(index.column())
        {
        case 0:
            return QString("T%1").arg(target->getID());
        case 1:
            return QString("%1").arg(s->getTime());
        case 2:
            return QString("%1").arg(s->getPositionX());
        case 3:
            return QString("%1").arg(s->getPositionY());
        case 4:
            return QString("%1").arg(s->getPositionZ());
        case 5:
            return QString("%1").arg(s->getSpeedX());
        case 6:
            return QString("%1").arg(s->getSpeedY());
        case 7:
            return QString("%1").arg(s->getSpeedZ());
        case 8:
            return QString("%1").arg(s->getAcceleratinX());
        case 9:
            return QString("%1").arg(s->getAcceleratinY());
        case 10:
            return QString("%1").arg(s->getAcceleratinZ());
        }
    }
    return QVariant();
}

QVariant TargetInfoTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    static QString headers[] = {"编号", "t", "sx", "sy", "sz", "vx", "vy", "vz", "ax", "ay", "az"};
    if (role != Qt::DisplayRole) return QVariant();
    if (orientation != Qt::Horizontal) return QVariant();
    return headers[section];
}
