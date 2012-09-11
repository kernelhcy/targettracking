#include "ttmap.h"
#include <QPainter>
#include <QSettings>
#include <vector>
#include <QDebug>


TTMap::TTMap(QWidget *parent) :
    QWidget(parent), targetGenerator(NULL), views(), timer(this), targetTracker(NULL)
{
    connect(&timer, SIGNAL(timeout()), this, SLOT(timeOutHandler()));
    margin = 25;
}

void TTMap::start()
{
    QSettings settings(SETTING_ORGANIZATION, SETTING_APPLICATION);
    int groupNumber = settings.value(SETTING_GROUP_NUMBER_KEY, 0).toInt();
    int targetNumber = settings.value(SETTING_GROUP_TARGET_NUMBER_KEY, 0).toInt();
    int skyGrpNumber = settings.value(SETTING_SKY_TARGET_NUMBER_KEY, 0).toInt();
    int groundGrpNumber = settings.value(SETTING_GROUND_TARGET_NUMBER_KEY, 0).toInt();

    qDebug() << "group number:" << groupNumber;
    qDebug() << "group target number:" << targetNumber;

    targetGenerator = new TargetGenerator(groupNumber, targetNumber, skyGrpNumber, groundGrpNumber);
    std::vector<TargetGroup*> *groups = targetGenerator->getGroups();
    std::vector<TargetGroup*>::iterator iter;
    for (iter = groups -> begin(); iter != groups -> end(); ++iter) {
        TargetGroupView *v = new TargetGroupView(*iter);
        views.append(v);
        qDebug() << "Group id : " << (*iter) -> getID();
    }

    // 将集群保存到全局变量中
    g_groups = groups;
    // 创建一个目标跟踪器
    targetTracker = new TargetTracker();

    // 启动定时器
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
    if (targetTracker) delete targetTracker;
}

/**
 * @brief TTMap::timeOutHandler
 * 超时处理函数。
 * 整个程序的驱动都是靠一个500ms触发一次的定时器。这个函数处理定时器的触发事件。
 * 也就是整个程序的心脏。所有的算法的入口都在这个地方。
 */
void TTMap::timeOutHandler()
{
    // 产生新的量测数据
    targetGenerator->go(1);

    // 对目标进行滤波
    targetTracker->tracking(targetGenerator->getCurrentStates());

    emit targetsUpdated();
    update();
}

void TTMap::paintEvent(QPaintEvent */*event*/)
{
    QPainter painter(this);
    //painter.setRenderHint(QPainter::Antialiasing, true);
    drawAxes(painter);

    QListIterator<TargetGroupView*> i(views);
    while (i.hasNext()) {
        i.next()->draw(painter, margin, width() - margin * 2, height() - margin * 2);
    }
}

void TTMap::mouseReleaseEvent(QMouseEvent *e)
{
    qDebug() << "Button click" << "(" << e->x() << "," << e->y() << ")";
    TargetGroup *g = getClickedTargetGroup(e->x(), e->y());
    if (g) {
        qDebug() << "click group:" << g->getID();
        QListIterator<TargetGroupView*> i(views);
        while (i.hasNext()) {
            TargetGroupView *v = i.next();
            v->setColor(QColor(0, 0, 255, 80));
            if (v->getTargetGroup() == g) {
                v->setColor(QColor(255, 0, 0, 255));
            }
        }

    } else {
        QListIterator<TargetGroupView*> i(views);
        while (i.hasNext()) {
            TargetGroupView *v = i.next();
            v->setColor(QColor(0, 0, 255, 255));
        }
    }
    emit targetSelectet(g);
    emit targetsUpdated();
    update();
}

TargetGroup* TTMap::getClickedTargetGroup(int x, int y)
{
    if (targetGenerator == NULL) return NULL;
    std::vector<TargetGroup*> *groups = targetGenerator->getGroups();
    std::vector<TargetGroup*>::iterator iter;
    TargetGroup *tg, *nearestGrp;
    float minDst = 0xffffffff, tmp;
    for (iter = groups -> begin(); iter != groups -> end(); ++iter) {
        tg = (*iter);
        tmp = getTargetGroupDist(tg, x, y);
        if (minDst > tmp) {
            minDst = tmp;
            nearestGrp = tg;
        }
    }
    // 最小距离大于10，认为没有选中任何目标
    if (minDst > 100) return NULL;
    return nearestGrp;
}

float TTMap::getTargetGroupDist(TargetGroup *grp, int x, int y)
{
    if (grp == NULL) return 0xffffffff;
    SingleTarget *t;
    State *s;
    float minDist = 0xffffffff, tmp;
    for (int i = 0; i < grp->getTargetCount(); ++i) {
        t = grp->getTarget(i);
        for (int j = 0; j < t->getStateCount(); ++j) {
            s = t->getState(j);
            float xx, yy;
            xx = width() * (s -> getPositionX()) / TTMap::WIDTH;
            yy = height() - height() * ( s -> getPositionY() ) / TTMap::HEIGHT;
            tmp = (xx - x) * (xx - x) + (yy - y) * (yy - y);
            if (minDist > tmp) {
                minDist = tmp;
            }
        }
    }
    qDebug() << grp->getID() << "minDst:" << minDist;
    return minDist;
}

void TTMap::drawAxes(QPainter &painter)
{
    int real_margin = margin - 5;

    // 画一个边框
    painter.setPen(QPen(Qt::black, 0.3));
    painter.drawRect(real_margin, real_margin
                     , width() - real_margin * 2, height() - real_margin * 2);

    painter.setPen(QPen(Qt::black, 0.2));
    // 单位提示
    QFont oldfont = painter.font();
    painter.setFont(QFont("Arial", 9));
    painter.drawText(width() - 150, 13, QString("单位：km, km/s"));
    painter.setFont(oldfont);

    painter.setPen(QPen(Qt::black, 1));
    // 原点
    painter.drawText(real_margin - 10, height() - real_margin + 10, QString("0"));
    // x轴坐标
    float step = (float)( width() - real_margin * 2) / (float)10;
    for (int i = 1; i <= 10; ++i) {
        float x, y;
        y = height() - real_margin + 20;
        x = step * i + real_margin;
        QString label = QString("%1").arg(i);
        painter.drawText(x - this->fontMetrics().width(label) / 2, y, label);
        painter.drawLine(x, height() - real_margin, x, height() - real_margin + 3);

        QPen oldpen = painter.pen();
        painter.setPen(QPen(Qt::black, 0.2, Qt::DashDotLine, Qt::RoundCap));
        painter.drawLine(x, height() - real_margin, x, real_margin);
        painter.setPen(oldpen);
    }

    // y轴坐标
    step = (float)(height() - real_margin * 2) / (float) 10 ;
    for (int i = 1; i <= 10; ++i) {
        float x, y;
        QString label = QString("%1").arg(i);
        x = real_margin;
        y = (10 - i) * step + real_margin;
        painter.drawText(x - this->fontMetrics().width(label) - 5
                         , y + this->fontMetrics().height() / 2 - 2, label);
        painter.drawLine(x - 3, y, x, y);

        QPen oldpen = painter.pen();
        painter.setPen(QPen(Qt::black, 0.2, Qt::DashDotLine, Qt::RoundCap));
        painter.drawLine(x, y, width() - real_margin, y);
        painter.setPen(oldpen);
    }
}
