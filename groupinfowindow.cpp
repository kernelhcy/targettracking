#include "groupinfowindow.h"
#include "ui_groupinfowindow.h"

GroupInfoWindow::GroupInfoWindow(TargetGroup *g, QWidget *parent) :
    QMainWindow(parent), grp(g),
    ui(new Ui::GroupInfoWindow)
{
    ui->setupUi(this);
    table = ui->tableView;
}

GroupInfoWindow::~GroupInfoWindow()
{
    delete ui;
}
