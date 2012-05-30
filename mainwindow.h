#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "settingdialog.h"
#include "groupinfowindow.h"
#include "ttmap.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void onSettingButtonClick();
    void onStartButtonToggled(bool);
    void onGroupInfoButtonClick();
private:
    Ui::MainWindow *ui;

    SettingDialog *settingDialog;
    GroupInfoWindow *grpInfoWindow;
    TTMap *map;
};

#endif // MAINWINDOW_H
