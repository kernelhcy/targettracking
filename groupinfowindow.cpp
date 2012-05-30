#include "groupinfowindow.h"
#include "ui_groupinfowindow.h"
#include "comm.h"
#include <QDebug>

GroupInfoWindow::GroupInfoWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GroupInfoWindow)
{
    ui->setupUi(this);
    table = ui->tableView;
    model = new GroupInfoTableModel(this);
    model->setGroupInfos(g_groups);
    table->setModel(model);

    // 隐藏行表头
    table->verticalHeader()->setHidden(true);
    // 第三列自动伸缩
    table->horizontalHeader()->setResizeMode(2, QHeaderView::Stretch);

    // 当行选择
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSelectionMode(QAbstractItemView::SingleSelection);

    // 自适应数据大小
    table->resizeColumnsToContents();
    table->resizeRowsToContents();

    connect(table, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(rowDoubleClicket(QModelIndex)));


}

GroupInfoWindow::~GroupInfoWindow()
{
    delete ui;
}

void GroupInfoWindow::rowDoubleClicket(const QModelIndex &index)
{
    int row = index.row();
    qDebug() << "double clicked row:" << row;
}
