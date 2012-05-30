#ifndef GROUPINFOWINDOW_H
#define GROUPINFOWINDOW_H

#include <QMainWindow>
#include <QTableView>
#include "model/TargetGroup.h"

namespace Ui {
class GroupInfoWindow;
}

class GroupInfoWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit GroupInfoWindow(TargetGroup *grp, QWidget *parent = 0);
    ~GroupInfoWindow();
    
private:
    Ui::GroupInfoWindow *ui;
    TargetGroup *grp;
    QTableView *table;
};

#endif // GROUPINFOWINDOW_H
