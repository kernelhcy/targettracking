#ifndef TTMAP_H
#define TTMAP_H

#include <QWidget>
#include <QList>
#include "datasource/targetgenerator.h"
#include "view/targetgroupview.h"
#include <QTimer>
#include <QMouseEvent>

/*
 * 地图
 * 用于显示目标
 */
class TTMap : public QWidget
{
    Q_OBJECT
public:
    explicit TTMap(QWidget *parent = 0);
    void paintEvent(QPaintEvent *);
    void mouseReleaseEvent(QMouseEvent *);

    // 所模拟的区域是10000 * 10000大小的区域
    const static int WIDTH = 10000;
    const static int HEIGHT = 10000;

public slots:
    // 开始跟踪
    void start();
    // 停止跟踪
    void stop();

    // 处理定时器的超时事件
    void timeOutHandler();

private:
    TargetGenerator *targetGenerator;
    QList<TargetGroupView*> views;

    QTimer timer;       // 定时器

    //
    // 获取被点击的集群
    //
    TargetGroup* getClickedTargetGroup(int x, int y);
    //
    // 判断集群是否被点击
    //
    bool isTargetGroupClicked(TargetGroup *grp, int x, int y);
};

#endif // TTMAP_H
