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
    // @param margin    留白
    // @param width     绘制区域的宽度
    // @param height    绘制区域的高度
    void draw(QPainter &painter, int margin, int width, int heigth);

    //
    // 设置获取目标颜色
    //
    void setColor(QColor);
    QColor getColor();

    bool isFilted(){ return isFiltedTarget; }
    void setFilted(bool filted) { isFiltedTarget = filted; }
private:
    SingleTarget *target;
    QColor color;
    bool isFiltedTarget;        // 标记目标是否是滤波产生的
};

#endif // SINGLETARGETVIEW_H
