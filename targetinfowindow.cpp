#include "targetinfowindow.h"
#include "ui_targetinfowindow.h"
#include <QDebug>

TargetInfoWindow::TargetInfoWindow(SingleTarget *t, QWidget *parent) :
    QMainWindow(parent), target(t),
    ui(new Ui::TargetInfoWindow)
{
    ui->setupUi(this);
    table = ui->tableView;
    model = new TargetInfoTableModel(t);
    table->setModel(model);
    // 隐藏行表头
    table->verticalHeader()->setHidden(true);
    for (int i = 0; i < model->columnCount(QModelIndex()); ++i) {
        table->horizontalHeader()->setResizeMode(i, QHeaderView::Stretch);
    }
    // 当行选择
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->setAutoScroll(true);

    connect(model, SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(updateTable(QModelIndex,QModelIndex)));
}

TargetInfoWindow::~TargetInfoWindow()
{
    delete ui;
    delete model;
}

void TargetInfoWindow::updateTable(QModelIndex start, QModelIndex end)
{

}
