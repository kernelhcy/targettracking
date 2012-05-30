#ifndef TARGETGROUPVIEW_H
#define TARGETGROUPVIEW_H
#include <QPainter>
#include <QColor>
#include "../model/TargetGroup.h"
#include "singletargetview.h"
#include <vector>

class TargetGroupView
{
public:
    TargetGroupView(TargetGroup *grp);
    ~TargetGroupView();
    //
    // 在屏幕的(0, 0)到(width, height)区域内绘制目标
    //
    // @param painter   画笔
    // @param width     绘制区域的宽度
    // @param height    绘制区域的高度
    void draw(QPainter &painter, int width, int heigth);

    //
    // 设置获取目标颜色
    //
    void setColor(QColor);
    QColor getColor();

private:
    TargetGroup *group;
    QColor color;
    std::vector<SingleTargetView*> views;
};

#endif // TARGETGROUPVIEW_H