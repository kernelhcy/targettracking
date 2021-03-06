#ifndef GROUPLISTTABLEMODEL_H
#define GROUPLISTTABLEMODEL_H

#include <QAbstractTableModel>
#include <vector>
#include "../model/TargetGroup.h"
//
// 集群信息表所对应的model
//
class GroupListTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit GroupListTableModel(QObject *parent = 0);
    
    // 设置集群信息
    void setGroupInfos(std::vector<TargetGroup*> *grps);

    // 获取行和列数
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;

    // 获取数据和表头
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

private:
    std::vector<TargetGroup*> *groups;
};

#endif // GROUPLISTTABLEMODEL_H
