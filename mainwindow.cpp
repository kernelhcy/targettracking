#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->settingBtn, SIGNAL(clicked()), this, SLOT(onSettingButtonClick()));
    connect(ui->groupInfoBtn, SIGNAL(clicked()), this, SLOT(onGroupInfoButtonClick()));
    connect(ui->startBtn, SIGNAL(toggled(bool)), this, SLOT(onStartButtonToggled(bool)));

    settingDialog = NULL;
    grpInfoWindow = NULL;

    map = new TTMap();
    QGridLayout *layout = new QGridLayout();
    layout -> addWidget(map);
    ui -> mapWidget -> setLayout(layout);

    //showMaximized();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onSettingButtonClick()
{
    if (settingDialog == NULL) {
        settingDialog = new SettingDialog(this);
    }
    settingDialog->show();
}

void MainWindow::onStartButtonToggled(bool toggled)
{
    if (toggled) {
        ui->startBtn->setText("停止跟踪");
        map->start();
        qDebug() << "开始跟踪...";
    } else {
        ui->startBtn->setText("开始跟踪");
        map->stop();
        qDebug() << "停止跟踪。";
    }
}

void MainWindow::onGroupInfoButtonClick()
{
    if (grpInfoWindow == NULL) {
        grpInfoWindow = new GroupInfoWindow(this);
    }
    grpInfoWindow->show();
}
