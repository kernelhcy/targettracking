#ifndef SINGLETARGET_H
#define SINGLETARGET_H
#include <vector>
#include "SystemModel.h"
#include "State.h"

class SingleTarget
{
public:
    SingleTarget(int i, const SystemModel& m, State &init):id(i), states(), model(m)
    {
        State * s = new State(init);
        states.push_back(s);
    }

    //拷贝构造函数
    SingleTarget(SingleTarget &t):id(t.id), states(), model(t.model)
    {
        ;
    }

    ~SingleTarget();

    virtual int getID();

    //
    // 目标运动time秒。
    // 计算目标运动time秒后的位置，并存储。
    //
    void go(int time);

    // 获取第i个状态
    State* getState(int i);
    // 获取状态数量
    int getStateCount();
    // 获取当前状态
    State* getCurrState();

    // 追加一个状态
    void addState(State s);

    //设置和获取运动模型
    void setModel(SystemModel &m);
    SystemModel getModel();

    //输出目标状态
    void print();

    //获取初始状态
    State* getInitState() { return states.at(0); }

private:
    int id;						// 目标id
    std::vector<State*> states;		// 目标状态集
    SystemModel model;			// 运动模型
};

#endif // SINGLETARGET_H
