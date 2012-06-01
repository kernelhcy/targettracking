#include "groupinfowindow.h"
#include "ui_groupinfowindow.h"
#include "targetinfowindow.h"
#include "model/singletarget.h"
#include <QDebug>

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

    connect(model, SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(updateTable()));
    connect(table, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(rowDoubleClicket(QModelIndex)));

    this->setWindowTitle(QString("集群G%1 详细信息").arg(g->getID()));
    ui->grpIDLabel->setText(QString("G%1").arg(grp->getID()));
    ui->targetNumLabel->setText(QString("%1").arg(model->rowCount(QModelIndex())));
}

GroupInfoWindow::~GroupInfoWindow()
{
    delete ui;
}

void GroupInfoWindow::updateTable()
{
    for (int i = 0; i < model->columnCount(QModelIndex()) ; ++i) {
        table->horizontalHeader()->setResizeMode(i, QHeaderView::Stretch);
    }
    if (isTracking) {
        ui->grpIDLabel->setText(QString("G%1").arg(grp->getID()));
        ui->targetNumLabel->setText(QString("%1").arg(model->rowCount(QModelIndex())));
    } else {
        ui->grpIDLabel->setText(QString("No Such Group."));
        ui->targetNumLabel->setText(QString("NAN"));
    }
}

void GroupInfoWindow::rowDoubleClicket(const QModelIndex &index)
{
    int row = index.row();
    qDebug() << "double clicked row:" << row;
    if (row >= grp->getTargetCount()) return;

    SingleTarget *t = grp->getTarget(row);
    TargetInfoWindow *tWin = new TargetInfoWindow(t, this);
    tWin->setVisible(true);
}
