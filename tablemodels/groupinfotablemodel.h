#ifndef GROUPINFOTABLEMODEL_H
#define GROUPINFOTABLEMODEL_H

#include <QAbstractTableModel>
#include "../model/TargetGroup.h"
#include <QTimer>

class GroupInfoTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit GroupInfoTableModel(TargetGroup *grp, QObject *parent = 0);
    
    // 设置集群信息
    void setGroup(TargetGroup *grp);

    // 获取行和列数
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;

    // 获取数据和表头
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

private:
    TargetGroup *grp;
    QTimer timer;
public slots:
    void updateTable();
};

#endif // GROUPINFOTABLEMODEL_H
