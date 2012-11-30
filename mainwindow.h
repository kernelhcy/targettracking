#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QSplashScreen>
#include "settingdialog.h"
#include "model/TargetGroup.h"
#include "grouplistwindow.h"
#include "ttmap.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QSplashScreen *splashScreen, QWidget *parent = 0);
    ~MainWindow();
public slots:
    void onSettingButtonClick();
    void onStartButtonToggled(bool);
    void onGroupInfoButtonClick();
    void onPauseButtonToggled(bool);

    // 处理TTMap中，目标数据更新信号
    void targetsUpdateHandler();
    // 处理TTMap中，有目标被选中的信号
    void targetSelectedHandler(TargetGroup *grp);

    void splashScreenTimerHandler();
private:
    Ui::MainWindow *ui;

    SettingDialog *settingDialog;
    GroupListWindow *grpInfoWindow;
    TTMap *map;

    QSplashScreen *splashScreen;
    QTimer splashTimer;

    TargetGroup *selectGrp;     // 选中的集群
    QLabel *idLabel, *tLabel;
    QLabel *vxLabel, *sxLabel, *axLabel;
    QLabel *vyLabel, *syLabel, *ayLabel;
    QLabel *vzLabel, *szLabel, *azLabel;
};

#endif // MAINWINDOW_H
