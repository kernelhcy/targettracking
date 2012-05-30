#ifndef SINGLETARGETVIEW_H
#define SINGLETARGETVIEW_H

#include "../model/singletarget.h"
#include <QPainter>
#include <QColor>

//
// 用于在地图上表示一个目标
//
class SingleTargetView
{
public:
    SingleTargetView(SingleTarget *t);

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
    SingleTarget *target;
    QColor color;

};

#endif // SINGLETARGETVIEW_H
