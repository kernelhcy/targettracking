#ifndef TARGETINFOWINDOW_H
#define TARGETINFOWINDOW_H

#include <QMainWindow>
#include "model/singletarget.h"
#include <QTableView>
#include "tablemodels/targetinfotablemodel.h"

namespace Ui {
class TargetInfoWindow;
}

class TargetInfoWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit TargetInfoWindow(SingleTarget *t, QWidget *parent = 0);
    ~TargetInfoWindow();
public slots:
    void updateTable(QModelIndex start, QModelIndex end);

private:
    Ui::TargetInfoWindow *ui;
    SingleTarget *target;

    QTableView *table;
    TargetInfoTableModel *model;
};

#endif // TARGETINFOWINDOW_H
