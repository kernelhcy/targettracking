#include "targetgenerator.h"
#include "../model/singletarget.h"
#include "../model/SystemModel.h"
#include <math.h>
TargetGenerator::TargetGenerator(int groupNum, int targetInGroupNum)
    : targetInGroupNumber(targetInGroupNum), groupNumber(groupNum), groups()
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
    for (int i = 0; i < groupNumber; ++i) {
        State initState(i * 300, 0,  0
                        , 50,   205, 0
                        , 8,    -5,  0
                        , 0);
        TargetGroup * grp = createGroup((i + 1) * 1000, initState, targetInGroupNumber);
        groups.push_back(grp);
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

std::vector<State> TargetGenerator::getCurrentStates()
{
    std::vector<State> states;
    std::vector<TargetGroup*>::iterator iter;
    State *s;
    TargetGroup *grp;
    SingleTarget *target;
    for ( iter = groups.begin(); iter != groups.end(); ++iter){
        grp = (*iter);
        int targetCount = grp -> getTargetCount();
        for (int i = 0; i < targetCount; ++i) {
            target = grp -> getTarget(i);
            s = target -> getCurrState();
            states.push_back(*s);
        }
    }
    return states;
}
