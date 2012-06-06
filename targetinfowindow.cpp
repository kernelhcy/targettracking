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

    this->setWindowTitle(QString("目标T%1 详细信息").arg(target->getID()));
    ui->targetIDLabel->setText(QString("T%1").arg(target->getID()));
    ui->stateNumLabel->setText(QString("%1").arg(target->getStateCount()));
}

TargetInfoWindow::~TargetInfoWindow()
{
    delete ui;
    delete model;
}

void TargetInfoWindow::updateTable(QModelIndex start, QModelIndex end)
{
    if (isTracking) {
        ui->targetIDLabel->setText(QString("T%1").arg(target->getID()));
        ui->stateNumLabel->setText(QString("%1").arg(target->getStateCount()));
    } else {
        ui->targetIDLabel->setText(QString("No Such Target..."));
        ui->stateNumLabel->setText(QString("NAN"));
    }
}
