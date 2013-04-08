#ifndef TARGETFILTER_H
#define TARGETFILTER_H

#include "../model/TargetGroup.h"
#include <map>
#include <vector>
#include "../model/State.h"
#include "../model/TargetState.h"
#include "filter/KalmanFilter.h"
#include "comm.h"
#include<Winsock2.h>
#pragma comment(lib,"ws2_32.lib")

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

    std::vector<TargetGroup*>* getTargetGroups(){ return &filtedTargetGrpsArray; }

private:
    std::map<int, KalmanFilter*> filters;            // 滤波器
    std::map<int, TargetGroup*> filtedTargetGrps;    // 滤波后的集群目标， 全局变量g_filted_groups
    std::vector<TargetGroup*> filtedTargetGrpsArray; // 集群目标数组。用于返回给外界。

    /**
     * @brief findFilter 查找目标对应的滤波器
     * @param grpId     集群id
     * @param targetId  目标id
     * @return          滤波器。如果没有找到，则创建一个滤波器并返回
     */
    KalmanFilter* findFilter(int grpId, int targetId);

    /**
     * @brief findTarget 查找对应的目标
     *
     * @param grpId     集群id
     * @param targetId  目标id
     * @return          目标。如果没有找到，则创建一个目标以及其对应的集群并返回。
     */
    SingleTarget* findTarget(int grpId, int targetId);

    /**
     * @brief printTargetGroups
     */
    void printTargetGroups();
    void sentMessage(char *sendBuf);
    void initMessage();
    void initSocketClient();

    SOCKET sockClient;
};

#endif // TARGETFILTER_H
