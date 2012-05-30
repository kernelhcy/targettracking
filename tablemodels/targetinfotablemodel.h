#ifndef TARGETINFOTABLEMODEL_H
#define TARGETINFOTABLEMODEL_H

#include <QAbstractTableModel>
#include <QTimer>
#include "../model/singletarget.h"

class TargetInfoTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit TargetInfoTableModel(SingleTarget *t, QObject *parent = 0);
    
    // 设置目标信息
    void setTarget(SingleTarget *target);

    // 获取行和列数
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;

    // 获取数据和表头
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

private:
    SingleTarget *target;
    QTimer timer;
public slots:
    void updateTable();
    
};

#endif // TARGETINFOTABLEMODEL_H
