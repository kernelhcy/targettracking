#ifndef GROUPINFOWINDOW_H
#define GROUPINFOWINDOW_H

#include <QMainWindow>
#include <QTableView>
#include "tablemodels/groupinfotablemodel.h"

namespace Ui {
class GroupInfoWindow;
}

class GroupInfoWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit GroupInfoWindow(QWidget *parent = 0);
    ~GroupInfoWindow();
    
public slots:
    void rowDoubleClicket(const QModelIndex& index);    // 双击行

private:
    Ui::GroupInfoWindow *ui;
    QTableView *table;
    GroupInfoTableModel *model;
};

#endif // GROUPINFOWINDOW_H
