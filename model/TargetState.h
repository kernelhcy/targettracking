#ifndef TARGETSTATE_H
#define TARGETSTATE_H

#include "State.h"

/**
 * @brief The TargetState class
 * 从数据关联模块中获取的某个目标的当前测量状态。
 */
class TargetState
{
public:
    TargetState(){}

public:
    int targetId;       // 目标id
    int groupId;        // 目标所在的集群id
    int time;           // 时间
    State state;        // 测量状态值
};

#endif // TARGETSTATE_H
