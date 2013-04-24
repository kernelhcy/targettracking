#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "model/singletarget.h"
#include <QDebug>

MainWindow::MainWindow(QSplashScreen *splash, QWidget *parent) :
    QMainWindow(parent), selectGrp(NULL), splashScreen(splash),
    ui(new Ui::MainWindow), splashTimer(this)
{
    ui->setupUi(this);
    connect(ui->settingBtn, SIGNAL(clicked()), this, SLOT(onSettingButtonClick()));
    connect(ui->groupInfoBtn, SIGNAL(clicked()), this, SLOT(onGroupInfoButtonClick()));
    connect(ui->startBtn, SIGNAL(toggled(bool)), this, SLOT(onStartButtonToggled(bool)));
    connect(ui->pauseBtn, SIGNAL(toggled(bool)), this, SLOT(onPauseButtonToggled(bool)));

    connect(&timer, SIGNAL(timeout()), this, SLOT(timeOutHandler()));

    settingDialog = NULL;
    grpInfoWindow = NULL;

    map = new TTMap();
    QGridLayout *layout = new QGridLayout();
    layout->setMargin(2);
    layout -> addWidget(map);
    ui -> mapWidget -> setLayout(layout);

    connect(map, SIGNAL(targetSelectet(TargetGroup*))
            , this, SLOT(targetSelectedHandler(TargetGroup*)));
    connect(map, SIGNAL(targetsUpdated()), this, SLOT(targetsUpdateHandler()));
    connect(&splashTimer, SIGNAL(timeout()), this, SLOT(splashScreenTimerHandler()));

    idLabel = ui->idLabel;
    tLabel = ui->tLabel;
    sxLabel = ui->sxLabel;
    axLabel = ui->axLabel;
    vxLabel = ui->vxLabel;
    syLabel = ui->syLabel;
    ayLabel = ui->ayLabel;
    vyLabel = ui->vyLabel;
    szLabel = ui->szLabel;
    azLabel = ui->azLabel;
    vzLabel = ui->vzLabel;

    //showMaximized();
    setMinimumSize(size());
    targetsUpdateHandler();
    splashTimer.start(2000);
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
        if (ui->pauseBtn->isChecked()) ui->pauseBtn->toggle();
        ui->pauseBtn->setEnabled(true);
        ui->groupInfoBtn->setEnabled(true);
        ui->settingBtn->setEnabled(false);
        ui->startBtn->setText("停止跟踪");
        map->start();
        qDebug() << "开始跟踪...";
        timer.start(5000);
    } else {
        if (ui->pauseBtn->isChecked()) ui->pauseBtn->toggle();
        ui->pauseBtn->setEnabled(false);
        ui->groupInfoBtn->setEnabled(false);
        ui->settingBtn->setEnabled(true);
        ui->startBtn->setText("开始跟踪");
        map->stop();
        qDebug() << "停止跟踪。";
        selectGrp = NULL;
        targetsUpdateHandler();
    }
    if (grpInfoWindow != NULL) grpInfoWindow->updateTable();
}

void MainWindow::onPauseButtonToggled(bool toggled)
{
    if (toggled) {
        ui->pauseBtn->setText("开始");
    } else {
        ui->pauseBtn->setText("暂停");
    }
    map->pause(!toggled);
}

void MainWindow::onGroupInfoButtonClick()
{
    if (grpInfoWindow == NULL) grpInfoWindow = new GroupListWindow(this);
    grpInfoWindow->show();
    grpInfoWindow->updateTable();
}

void MainWindow::targetSelectedHandler(TargetGroup *grp)
{
    selectGrp = grp;
}

void MainWindow::targetsUpdateHandler()
{
    if (selectGrp) {
        idLabel->setText(QString("G%1").arg(selectGrp->getID()));
        SingleTarget *t = selectGrp->getTarget(0);
        if (t) {
            sxLabel->setText(QString("%1").arg(t->getCurrState()->getPositionX()));
            syLabel->setText(QString("%1").arg(t->getCurrState()->getPositionY()));
            szLabel->setText(QString("%1").arg(t->getCurrState()->getPositionZ()));
            vxLabel->setText(QString("%1").arg(t->getCurrState()->getSpeedX()));
            vyLabel->setText(QString("%1").arg(t->getCurrState()->getSpeedY()));
            vzLabel->setText(QString("%1").arg(t->getCurrState()->getSpeedZ()));
            axLabel->setText(QString("%1").arg(t->getCurrState()->getAcceleratinX()));
            ayLabel->setText(QString("%1").arg(t->getCurrState()->getAcceleratinY()));
            azLabel->setText(QString("%1").arg(t->getCurrState()->getAcceleratinZ()));
        }
    } else {
        idLabel->setText("NAN");
        tLabel->setText("0");
        sxLabel->setText("0");
        syLabel->setText("0");
        szLabel->setText("0");
        axLabel->setText("0");
        ayLabel->setText("0");
        azLabel->setText("0");
        vxLabel->setText("0");
        vyLabel->setText("0");
        vzLabel->setText("0");
    }
}

//开场
void MainWindow::splashScreenTimerHandler()
{
    show();
    splashScreen -> finish(this);
    delete splashScreen;
    splashTimer.stop();
}

void MainWindow::timeOutHandler()
{
    ui->startTrackLineEdit->setText("5.23");
    ui->daCorrectnessLineEdit->setText("98.11");
    ui->trackCorrectnessLineEdit->setText("95.76");
}
