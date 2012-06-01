#include "groupinfotablemodel.h"
#include "model/singletarget.h"
#include "model/State.h"

GroupInfoTableModel::GroupInfoTableModel(TargetGroup *g, QObject *parent) :
    QAbstractTableModel(parent), grp(g), timer(this)
{
    connect(&timer, SIGNAL(timeout()), this, SLOT(updateTable()));
    timer.start(500);
}


// 定时刷新数据
void GroupInfoTableModel::updateTable()
{
    if (!isTracking){
        grp = NULL;
        reset();    // 跟新数据，使table和model同步
        timer.stop();
    }
    emit dataChanged(this->index(0, 0), this->index(rowCount(QModelIndex()), columnCount(QModelIndex())));
}

void GroupInfoTableModel::setGroup(TargetGroup *grp)
{
    this->grp = grp;
}

int GroupInfoTableModel::rowCount(const QModelIndex &parent) const
{
    if (grp == NULL) return 0;
    return grp->getTargetCount();
}

int GroupInfoTableModel::columnCount(const QModelIndex &parent) const
{
    return 12;
}

QVariant GroupInfoTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) return QVariant();
    if (role == Qt::TextAlignmentRole) {
        return int(Qt::AlignCenter | Qt::AlignVCenter);
    } else if (role == Qt::DisplayRole) {
        SingleTarget *t = grp->getTarget(index.row());
        switch(index.column())
        {
        case 0:
            return QString("T%1").arg(t->getID());
        case 1:
            return QString("G%1").arg(grp->getID());
        case 2:
            return QString("%1").arg(t->getCurrState()->getTime());
        case 3:
            return QString("%1").arg(t->getCurrState()->getPositionX());
        case 4:
            return QString("%1").arg(t->getCurrState()->getPositionY());
        case 5:
            return QString("%1").arg(t->getCurrState()->getPositionZ());
        case 6:
            return QString("%1").arg(t->getCurrState()->getSpeedX());
        case 7:
            return QString("%1").arg(t->getCurrState()->getSpeedY());
        case 8:
            return QString("%1").arg(t->getCurrState()->getSpeedZ());
        case 9:
            return QString("%1").arg(t->getCurrState()->getAcceleratinX());
        case 10:
            return QString("%1").arg(t->getCurrState()->getAcceleratinY());
        case 11:
            return QString("%1").arg(t->getCurrState()->getAcceleratinZ());
        case 12:
            return QString("%1").arg(t->getCurrState()->getTime());
        }
    }
    return QVariant();
}

QVariant GroupInfoTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    static QString headers[] = {"编号", "集群编号", "t", "sx", "sy", "sz", "vx", "vy", "vz", "ax", "ay", "az", "空/地"};
    if (role != Qt::DisplayRole) return QVariant();
    if (orientation != Qt::Horizontal) return QVariant();
    return headers[section];
}
