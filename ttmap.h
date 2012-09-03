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

    // 所模拟的区域大小
    const static int WIDTH = 10000;
    const static int HEIGHT = 10000;

signals:
    // 目标位置更新是发送此信号
    void targetsUpdated();

    //
    // 当有目标被选中的时候，发送此信号。
    // grp可以为NULL, 为NULL的时候表示没有目标被选中
    //
    void targetSelectet(TargetGroup *grp);

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

    int margin;         // 坐标系周围的留白
    QTimer timer;       // 定时器

    //
    // 获取被点击的集群
    //
    TargetGroup* getClickedTargetGroup(int x, int y);
    //
    // 计算点击的点和集群的最近距离
    //
    float getTargetGroupDist(TargetGroup *grp, int x, int y);

    //
    // 绘制坐标系
    //
    void drawAxes(QPainter &painter);
};

#endif // TTMAP_H
