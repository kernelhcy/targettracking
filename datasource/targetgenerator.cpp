#include "targetgenerator.h"
#include "../model/singletarget.h"
#include "../model/SystemModel.h"
#include <math.h>
#include <QtGlobal>

static State states[30] = {
    // 地面集群初始化状态
    State(300, -30, 0, 50, 105, 0,    1, 1, 0, 0),
    State(300, -30, 0, 5, 95, 0,      2, 3, 0, 0),
    State(300, -30, 0, 150, 85, 0,    1, -2, 0, 0),
    State(300, -30, 0, 50, 75, 0,     2, 1, 0, 0),
    State(300, -30, 0, 40, 65, 0,     3, 2, 0, 0),
    State(300, -30, 0, 30, 55, 0,     -1, 1, 0, 0),
    State(300, -30, 0, 20, 45, 0,     2, 2, 0, 0),
    State(300, -30, 0, 10, 35, 0,     3, 1, 0, 0),
    State(300, -30, 0, 140, 25, 0,    -2, 1, 0, 0),
    State(300, -30, 0, -130, 15, 0,   3, 2, 0, 0),
    State(300, -30, 0, 120, 25, 0,   2, 2, 0, 0),
    State(300, -30, 0, 110, 45, 0,   -1, 3, 0, 0),
    State(300, -30, 0, 100, 245, 0,   3, -2, 0, 0),
    State(300, -30, 0, -50, 175, 0,   2, -1, 0, 0),
    State(300, -30, 0, -30, 135, 0,  3, 2, 0, 0),
    // 空中集群初始化状态
    State(300, 0, 0, 50, 205, 0, 8, -5, 0, 0),
    State(300, 0, 0, 50, 205, 0, 8, -5, 0, 0),
    State(300, 0, 0, 50, 205, 0, 8, -5, 0, 0),
    State(300, 0, 0, 50, 205, 0, 8, -5, 0, 0),
    State(300, 0, 0, 50, 205, 0, 8, -5, 0, 0),
    State(300, 0, 0, 50, 205, 0, 8, -5, 0, 0),
    State(300, 0, 0, 50, 205, 0, 8, -5, 0, 0),
    State(300, 0, 0, 50, 205, 0, 8, -5, 0, 0),
    State(300, 0, 0, 50, 205, 0, 8, -5, 0, 0),
    State(300, 0, 0, 50, 205, 0, 8, -5, 0, 0),
    State(300, 0, 0, 50, 205, 0, 8, -5, 0, 0),
    State(300, 0, 0, 50, 205, 0, 8, -5, 0, 0),
    State(300, 0, 0, 50, 205, 0, 8, -5, 0, 0),
    State(300, 0, 0, 50, 205, 0, 8, -5, 0, 0),
    State(300, 0, 0, 50, 205, 0, 8, -5, 0, 0)
};

TargetGenerator::TargetGenerator(int groupNum, int targetInGroupNum, int skyGroupNumber, int groundGroupNumber)
    : targetInGroupNumber(targetInGroupNum), groupNumber(groupNum), groups()
    , skyGroupNumber(skyGroupNumber), groundGroupNumber(groundGroupNumber)
{
    initGroups();
}
TargetGenerator::~TargetGenerator()
{
    std::vector<TargetGroup*>::iterator iter;
    for ( iter = groups.begin(); iter != groups.end(); ++iter){
        delete (*iter);
    }
}

void TargetGenerator::go(int time)
{
    std::vector<TargetGroup*>::iterator iter;
    for ( iter = groups.begin(); iter != groups.end(); ++iter){
        (*iter) -> go(time);
    }
}

std::vector<TargetGroup*>* TargetGenerator::getGroups()
{
    return &groups;
}

void TargetGenerator::initGroups()
{
    int groupId = 1;
    // 地面集群
    for (int i = 0; i < groundGroupNumber; ++i) {
        int index = qrand() % 15;
        State initState = states[index];
        initState.setPositionX(groupId * 300);
        TargetGroup * grp = createGroup(groupId * 1000, initState, targetInGroupNumber);
        groups.push_back(grp);
        ++groupId;
    }

    // 空中集群
    for (int i = 0; i < skyGroupNumber; ++i) {
        int index = qrand() % 15;
        State initState = states[index + 15];
        initState.setPositionX(groupId * 300);
        TargetGroup * grp = createGroup(groupId * 1000, initState, targetInGroupNumber);
        groups.push_back(grp);
        ++groupId;
    }
}

//
// 构造一个集群
//
// @param initState 初始状态
// @param targetNum 目标数量
TargetGroup* TargetGenerator::createGroup(int id, State initState, int targetNum)
{
    TargetGroup *grp;
    SingleTarget *target;
    grp = new TargetGroup(id);
    State init = initState;
    //init.setPositionX(init.getPositionX() + 500 * i);
    int column = (int)(std::sqrt(targetNum));
    for (int r = 0, k = 0; k < targetNum; ++r) {
        for (int c = 0; c < column && k < targetNum; ++c, ++k) {
            State s = init;
            s.setPositionX(init.getPositionX() + c * 150);
            s.setPositionY(init.getPositionY() + r * 150);
            target = new SingleTarget(k + id, SystemModel::getModel(SystemModel::CV), s);
            grp -> addTarget(target);
        }
    }
    return grp;
}

std::vector<TargetState> TargetGenerator::getCurrentStates()
{
    std::vector<TargetState> states;
    std::vector<TargetGroup*>::iterator iter;
    State *s;
    TargetGroup *grp;
    SingleTarget *target;
    TargetState tState;
    for ( iter = groups.begin(); iter != groups.end(); ++iter){
        grp = (*iter);
        int targetCount = grp -> getTargetCount();
        for (int i = 0; i < targetCount; ++i) {
            target = grp -> getTarget(i);
            s = target -> getCurrState();
            tState.groupId = grp->getID();
            tState.targetId = target->getID();
            tState.state = *s;
            states.push_back(tState);
        }
    }
    return states;
}
