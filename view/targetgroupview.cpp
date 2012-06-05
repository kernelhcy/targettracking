#include "targetgroupview.h"

TargetGroupView::TargetGroupView(TargetGroup *grp): group(grp), color(Qt::blue), views()
{
    SingleTarget *t;
    int targetCount = group -> getTargetCount();
    for (int i = 0; i < targetCount; ++i ) {
        t = group -> getTarget(i);
        SingleTargetView *view = new SingleTargetView(t);
        view -> setColor(color);
        views.push_back(view);
    }
}

TargetGroupView::~TargetGroupView()
{
    std::vector<SingleTargetView*>::iterator iter;
    for (iter = views.begin(); iter != views.end(); ++iter) {
        delete (*iter);
    }
}

void TargetGroupView::draw(QPainter &painter, int margin, int width, int height)
{
    std::vector<SingleTargetView*>::iterator iter;
    for (iter = views.begin(); iter != views.end(); ++iter) {
        (*iter) -> draw(painter, margin, width, height);
    }
}

void TargetGroupView::setColor(QColor c)
{
    color = c;
    std::vector<SingleTargetView*>::iterator iter;
    for (iter = views.begin(); iter != views.end(); ++iter) {
        (*iter) -> setColor(c);
    }
}

QColor TargetGroupView::getColor()
{
    return color;
}
