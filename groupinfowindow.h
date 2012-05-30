#ifndef GROUPINFOWINDOW_H
#define GROUPINFOWINDOW_H

#include <QMainWindow>
#include <QTableView>
#include "model/TargetGroup.h"
#include "tablemodels/groupinfotablemodel.h"
namespace Ui {
class GroupInfoWindow;
}

class GroupInfoWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit GroupInfoWindow(TargetGroup *grp, QWidget *parent = 0);
    ~GroupInfoWindow();
    
public slots:
    void updateTable();
    void rowDoubleClicket(const QModelIndex &index);

private:
    Ui::GroupInfoWindow *ui;
    TargetGroup *grp;
    QTableView *table;
    GroupInfoTableModel *model;
};

#endif // GROUPINFOWINDOW_H
