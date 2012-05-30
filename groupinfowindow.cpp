#include "groupinfowindow.h"
#include "ui_groupinfowindow.h"

GroupInfoWindow::GroupInfoWindow(TargetGroup *g, QWidget *parent) :
    QMainWindow(parent), grp(g),
    ui(new Ui::GroupInfoWindow)
{
    ui->setupUi(this);
    table = ui->tableView;
    model = new GroupInfoTableModel(g);
    table->setModel(model);
    // 隐藏行表头
    table->verticalHeader()->setHidden(true);
    for (int i = 0; i < model->columnCount(QModelIndex()); ++i) {
        table->horizontalHeader()->setResizeMode(i, QHeaderView::Stretch);
    }
    // 当行选择
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSelectionMode(QAbstractItemView::SingleSelection);

    // 自适应数据大小
    table->resizeColumnsToContents();
    table->resizeRowsToContents();

    connect(model, SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(updateTable()));
}

GroupInfoWindow::~GroupInfoWindow()
{
    delete ui;
}

void GroupInfoWindow::updateTable()
{
    // 自适应数据大小
    table->resizeColumnsToContents();
    table->resizeRowsToContents();
    for (int i = 0; i < model->columnCount(QModelIndex()) ; ++i) {
        table->horizontalHeader()->setResizeMode(i, QHeaderView::Stretch);
    }
}
