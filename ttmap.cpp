#include "ttmap.h"
#include <QPainter>
#include <QSettings>
#include <vector>
#include <QDebug>


TTMap::TTMap(QWidget *parent) :
    QWidget(parent), targetGenerator(NULL), views(), timer(this)
{
    connect(&timer, SIGNAL(timeout()), this, SLOT(timeOutHandler()));
}

void TTMap::start()
{
    QSettings settings("sslib", "targettracking");
    int groupNumber = settings.value("group number", 0).toInt();
    int targetNumber = settings.value("group target number", 0).toInt();

    qDebug() << "group number:" << groupNumber;
    qDebug() << "group target number:" << targetNumber;

    targetGenerator = new TargetGenerator(groupNumber, targetNumber);
    std::vector<TargetGroup*> *groups = targetGenerator->getGroups();
    std::vector<TargetGroup*>::iterator iter;
    for (iter = groups -> begin(); iter != groups -> end(); ++iter) {
        TargetGroupView *v = new TargetGroupView(*iter);
        views.append(v);
        qDebug() << "Group id : " << (*iter) -> getID();
    }

    // 将集群保存到全局变量中
    g_groups = groups;
    timer.start(500);
    isTracking = true;
}

void TTMap::stop()
{
    isTracking = false;
    timer.stop();
    // 清除旧数据
    QListIterator<TargetGroupView*> i(views);
    while (i.hasNext()) {
        delete i.next();
    }
    views.clear();
    update();
    if (targetGenerator) delete targetGenerator;
    g_groups = NULL;
}

void TTMap::timeOutHandler()
{
    targetGenerator->go(1);

//    qDebug() << "Current states:";
//    std::vector<State> states = targetGenerator->getCurrentStates();
//    std::vector<State>::iterator iter;
//    for (iter = states.begin(); iter != states.end(); ++iter) {
//        (*iter).print();
//    }

    update();
}

void TTMap::paintEvent(QPaintEvent */*event*/)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    QListIterator<TargetGroupView*> i(views);
    while (i.hasNext()) {
        i.next()->draw(painter, width(), height());
    }
}

void TTMap::mouseReleaseEvent(QMouseEvent *e)
{
    qDebug() << "Button click" << "(" << e->x() << "," << e->y() << ")";
    TargetGroup *g = getClickedTargetGroup(e->x(), e->y());
    if (g) qDebug() << "click group:" << g->getID();
}

TargetGroup* TTMap::getClickedTargetGroup(int x, int y)
{
    std::vector<TargetGroup*> *groups = targetGenerator->getGroups();
    std::vector<TargetGroup*>::iterator iter;
    TargetGroup *tg;
    for (iter = groups -> begin(); iter != groups -> end(); ++iter) {
        tg = (*iter);
        if (isTargetGroupClicked(tg, x, y)) {
            return tg;
        }
    }
    return NULL;
}

bool TTMap::isTargetGroupClicked(TargetGroup *grp, int x, int y)
{
    if (grp == NULL) return false;
    SingleTarget *t;
    State *s;
    for (int i = 0; i < grp->getTargetCount(); ++i) {
        t = grp->getTarget(i);
        for (int j = 0; j < t->getStateCount(); ++j) {
            s = t->getState(j);
            float xx, yy;
            xx = width() * (s -> getPositionX()) / TTMap::WIDTH;
            yy = height() - height() * ( s -> getPositionY() ) / TTMap::HEIGHT;
            if (qAbs(xx - x) < 5 && qAbs(yy - y) < 5) {
                return true;
            }
        }
    }
    return false;
}
