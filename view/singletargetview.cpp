#include "singletargetview.h"
#include <QDebug>
#include "ttmap.h"

SingleTargetView::SingleTargetView(SingleTarget *t): target(t), color(Qt::black)
{
}

void SingleTargetView::draw(QPainter &painter, int margin, int width, int height)
{
    painter.setPen(QPen(color, 1));

    State * s;
    int stateCount = target -> getStateCount();
    int x, y, w, h;
    w = h = 2; // 点的大小
    for (int i = 0; i < stateCount; ++i) {
        s = target -> getState(i);
        if (!s) continue;
        //
        // 虚拟目标区域的大小是10000*10000.
        //
        x = width * (s -> getPositionX()) / TTMap::WIDTH + margin;
        y = height - height * ( s -> getPositionY() ) / TTMap::HEIGHT + margin;
        //qDebug("draw point at (%d, %d) in (%d, %d)", x, y, width, height);
        if (i == stateCount - 1) {
            w = h = 4;
        }

        // 状态点超出屏幕范围
        if (s->getPositionX() > TTMap::WIDTH || s->getPositionY() > TTMap::HEIGHT) continue;

        painter.fillRect(x, y, w, h, QBrush(color, Qt::SolidPattern));
    }
}

QColor SingleTargetView::getColor()
{
    return color;
}

void SingleTargetView::setColor(QColor c)
{
    color = c;
}
