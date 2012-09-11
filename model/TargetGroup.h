#pragma once
#include <vector>
#include "SystemModel.h"
#include "singletarget.h"
/*
 * 表示一个目标集群。
 * @author hcy
 */
class TargetGroup
{
public:
    TargetGroup(int id);
    ~TargetGroup();
    virtual int getID();

    //
    // 目标运动time秒。
    // 计算目标运动time秒后的位置，并存储。
    //
    void go(int time);


    //输出目标状态
    void print();

    //
    // 添加一个目标
    //
    // @param t 所要添加的目标
    void addTarget(SingleTarget *t);

    // 删除一个目标
    void deleteTarget(SingleTarget *t);
    void deleteTarget(int id);

    // 获取一个目标
    SingleTarget* getTarget(size_t index);
    SingleTarget* getTargetByID(int id);

    // 获取当前集群中的目标数量
    int getTargetCount();

    // 构造一个副本
    TargetGroup* clone();
private:
    int id;                         // 集群id
    std::vector<SingleTarget*> targets;        // 目标
};

