#ifndef TARGETGENERATOR_H
#define TARGETGENERATOR_H

#include "../model/TargetGroup.h"
#include <vector>
#include "../model/State.h"
//
// 用于生成目标数据
//
class TargetGenerator
{
public:
    //
    // 构造一个目标生成器
    //
    // @param groupNum              集群数量
    // @param targetInGroupNum      集群中目标的数量
    TargetGenerator(int groupNum, int targetInGroupNum, int skyGroupNumber, int groundGroupNumber);
    ~TargetGenerator();

    void go(int time);
    std::vector<TargetGroup*>* getGroups();

    //
    // 获取当前所有目标的状态。模拟雷达输出的数据
    // 返回的是一个vector，不是vector指针。
    //
    std::vector<State> getCurrentStates();

private:
    std::vector<TargetGroup*> groups;
    int targetInGroupNumber;
    int groupNumber;

    int skyGroupNumber;         // 空中集群数目
    int groundGroupNumber;      // 地面集群数目

    void initGroups();
    TargetGroup* createGroup(int id, State initState, int targetNum);
};

#endif // TARGETGENERATOR_H
