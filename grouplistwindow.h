#ifndef GROUPLISTWINDOW_H
#define GROUPLISTWINDOW_H

#include <QMainWindow>
#include <QTableView>
#include "tablemodels/grouplisttablemodel.h"

namespace Ui {
class GroupListWindow;
}

class GroupListWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit GroupListWindow(QWidget *parent = 0);
    ~GroupListWindow();
    void updateTable();
    
public slots:
    void rowDoubleClicket(const QModelIndex& index);    // 双击行

private:
    Ui::GroupListWindow *ui;
    QTableView *table;
    GroupListTableModel *model;
};

#endif // GROUPINFOWINDOW_H
