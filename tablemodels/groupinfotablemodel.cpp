#include "groupinfotablemodel.h"

GroupInfoTableModel::GroupInfoTableModel(QObject *parent) :
    QAbstractTableModel(parent), groups(NULL)
{
}

int GroupInfoTableModel::rowCount(const QModelIndex &parent) const
{
    if (groups == NULL) return 0;
    return groups->size();
}

int GroupInfoTableModel::columnCount(const QModelIndex &parent) const
{
    return 3;
}

void GroupInfoTableModel::setGroupInfos(std::vector<TargetGroup*> *grps)
{
    groups = grps;
}

QVariant GroupInfoTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) return QVariant();
    if (role == Qt::TextAlignmentRole) {
        switch(index.column())
        {
        case 0:
        case 1:
            return int(Qt::AlignCenter | Qt::AlignVCenter);
        case 2:
            return int(Qt::AlignLeft | Qt::AlignVCenter);
        case 3:
            break;
        }

    } else if (role == Qt::DisplayRole) {
        TargetGroup *grp = groups->at(index.row());
        switch(index.column())
        {
        case 0:
            return QString("G%1").arg(grp->getID());
        case 1:
            return QString("%1").arg(grp->getTargetCount());
        case 2:
            QString tmp;
            int targetCount = grp->getTargetCount();
            for (int i = 0; i < targetCount; ++i) {
                tmp.append(QString("T%1").arg(grp->getTarget(i)->getID()));
                tmp.append(" ");
            }
            return tmp;

        }
    }
    return QVariant();
}

QVariant GroupInfoTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    static QString headers[3] = {"编号", "包含目标数", "包含目标编号"};
    if (role != Qt::DisplayRole) return QVariant();
    if (orientation != Qt::Horizontal) return QVariant();
    return headers[section];
}
