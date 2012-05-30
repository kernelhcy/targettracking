#include "singletarget.h"
#include <QDebug>
SingleTarget::~SingleTarget()
{
    std::vector<State*>::iterator it;
    for(it = states.begin(); it != states.end(); ++it)
    {
        delete (*it);
    }
}

//
// 目标运动time秒。
// 计算目标运动time秒后的位置，并存储。
//
void SingleTarget::go(int time)
{
    Matrix tmp = states.at(states.size() - 1) -> getData();
    const Matrix f = model.GetF();

    for(int i = 0; i < time; ++i)
    {
        tmp = f * tmp;
    }

    State *newState = new State(*states.at(states.size() - 1));
    newState -> setData(tmp);
    newState -> setTime(newState -> getTime() + time);

    states.push_back(newState);
}
int SingleTarget::getID()
{
    return id;
}

void SingleTarget::addState(State s)
{
    State *newState = new State(s);
    states.push_back(newState);
}

// 获取第i个状态
State* SingleTarget::getState(int i)
{
    return states.at(i);
}
// 获取状态数量
int SingleTarget::getStateCount()
{
    return states.size();
}
// 获取当前状态
State* SingleTarget::getCurrState()
{
    return states.at(states.size() - 1);
}

//设置和获取运动模型
void SingleTarget::setModel(SystemModel &m)
{
    model = m;
}
SystemModel SingleTarget::getModel()
{
    return model;
}

void SingleTarget::print()
{
    qDebug() << "\tTarget" << id << ":";
    std::vector<State*>::iterator it;
    for(it = states.begin(); it != states.end(); ++it)
    {
        (*it) -> print();
    }
}
