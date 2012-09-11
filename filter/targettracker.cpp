#include "targettracker.h"
#include <QDebug>

TargetTracker::TargetTracker()
{
    targetGrps = g_groups;
    filtedTargetGrps = new std::vector<TargetGroup*>();
    std::vector<TargetGroup*>::iterator iter;
    for (iter = targetGrps -> begin(); iter != targetGrps -> end(); ++iter)
    {
        filtedTargetGrps -> push_back((*iter) -> clone());
    }
    filters = new std::vector<KalmanFilter*>();
}

TargetTracker::~TargetTracker()
{
    targetGrps = NULL;
    delete filters;
    std::vector<TargetGroup*>::iterator iter;
    for (iter = targetGrps -> begin(); iter != targetGrps -> end(); ++iter)
    {
        delete (*iter);
    }
    delete filtedTargetGrps;
}

void TargetTracker::tracking(std::vector<TargetState> states)
{
    std::vector<TargetState>::iterator iter;
    TargetState tState;
    for (iter = states.begin(); iter != states.end(); ++iter)
    {
        tState = *iter;
        qDebug() << tState.groupId << tState.targetId;
        tState.state.print();
    }
}
