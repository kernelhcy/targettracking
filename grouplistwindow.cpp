#include "grouplistwindow.h"
#include "ui_grouplistwindow.h"
#include "comm.h"
#include <QDebug>
#include "groupinfowindow.h"

GroupListWindow::GroupListWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GroupListWindow)
{
    ui->setupUi(this);
    table = ui->tableView;
    model = new GroupListTableModel(this);
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

GroupListWindow::~GroupListWindow()
{
    delete ui;
}

void GroupListWindow::rowDoubleClicket(const QModelIndex &index)
{
    int row = index.row();
    qDebug() << "double clicked row:" << row;
    if (row >= g_groups->size()) return;

    TargetGroup *grp = g_groups->at(row);
    GroupInfoWindow *infoWin = new GroupInfoWindow(grp, this);
    infoWin->setVisible(true);
}
