#include "targettracker.h"
#include <QDebug>

TargetTracker::TargetTracker(): filters(), filtedTargetGrps()
{
}

TargetTracker::~TargetTracker()
{
    std::map<int, KalmanFilter*>::const_iterator iter1;
    for(iter1 = filters.begin(); iter1 != filters.end(); ++iter1){
        delete (iter1 -> second);
    }

    std::map<int, TargetGroup*>::const_iterator iter;
    for (iter = filtedTargetGrps.begin(); iter != filtedTargetGrps.end(); ++iter)
    {
        delete (iter -> second);
    }
}

void TargetTracker::tracking(std::vector<TargetState> states)
{
    std::vector<TargetState>::const_iterator iter;
    TargetState tState;
    KalmanFilter *filter;
    SingleTarget *target;
    for (iter = states.begin(); iter != states.end(); ++iter)
    {
        tState = *iter;

        filter = findFilter(tState.groupId, tState.targetId);
        target = findTarget(tState.groupId, tState.targetId);
        if (target == NULL) continue;
        if (filter == NULL) continue;
        if (target->getStateCount() == 0) {
            // 第一次获取目标的状态，直接保存，不做任何计算。
            target->addState(tState.state);
            filter->setState(tState.state.getData());
            continue;
        }

        // 计算一步预测值
        Matrix matrix = filter->estimate();
        // 根据测量值更新预测数据
        filter->updateByMeasure(tState.state.getData());

        State s;
        s.setData(matrix);
        s.setTime(tState.time);
        target->addState(s);
    }

    printTargetGroups();
}

KalmanFilter* TargetTracker::findFilter(int grpId, int targetId)
{
    KalmanFilter *filter = NULL;
    filter = filters[grpId * 100000 + targetId];
    if (filter == NULL) {
        filter = new KalmanFilter();    // 使用默认的运动模型
        filter->setGroupId(grpId);
        filter->setTargetId(targetId);
        filters[grpId * 100000 + targetId] = filter;
    }
    return filter;
}

SingleTarget* TargetTracker::findTarget(int grpId, int targetId)
{
    TargetGroup *tg = NULL;
    tg = filtedTargetGrps[grpId];
    if (tg == NULL) {
        // 没有找到对应的集群，创建一个新的集群.
        tg = new TargetGroup(grpId);
        filtedTargetGrps[grpId] = tg;
    }
    SingleTarget *t = tg->getTargetByID(targetId);
    if (t == NULL) {
        // 没有找到对应的目标，创建一个目标.
        t = new SingleTarget(targetId);
        tg->addTarget(t);
    }
    return t;
}

void TargetTracker::printTargetGroups()
{
    TargetGroup *tg = NULL;
    std::map<int, TargetGroup*>::const_iterator iter;
    for (iter = filtedTargetGrps.begin(); iter != filtedTargetGrps.end(); ++iter)
    {
        tg = (iter -> second);
        tg->print();
    }
}
