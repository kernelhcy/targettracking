#ifndef TARGETFILTER_H
#define TARGETFILTER_H

#include "../model/TargetGroup.h"
#include <vector>
#include "../model/State.h"
#include "../model/TargetState.h"
#include "filter/KalmanFilter.h"
#include "comm.h"

/**
 * @brief The TargetTracker class
 * 目标跟踪器
 * 通过各个目标当前的最新测量值，计算起滤波值。
 */
class TargetTracker
{
public:
    TargetTracker();
    ~TargetTracker();

    /**
     * @brief 跟踪目标，更新目标状态。
     * @param states 各个目标对应的当前测量值。
     */
    void tracking(std::vector<TargetState> states);

private:
    std::vector<KalmanFilter*> *filters;            // 滤波器
    std::vector<TargetGroup*> *targetGrps;          // 目标集群， 引用全局变量g_groups
    std::vector<TargetGroup*> *filtedTargetGrps;    // 滤波后的集群目标， 全局变量g_filted_groups
};

#endif // TARGETFILTER_H
