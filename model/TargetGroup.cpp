#include "TargetGroup.h"
#include <QDebug>

TargetGroup::TargetGroup(int id)
    : targets()
{
	this -> id = id;
}

TargetGroup::~TargetGroup()
{
    std::vector<SingleTarget*>::iterator it;
    for(it = targets.begin(); it != targets.end(); ++it) {
       delete (*it);
    }
}

void TargetGroup::go(int time)
{
    std::vector<SingleTarget*>::iterator it;
    for(it = targets.begin(); it != targets.end(); ++it) {
        (*it) -> go(time);
    }
}

void TargetGroup::print()
{
    qDebug() << "Target Group" << id << ":";
    std::vector<SingleTarget*>::iterator it;
    for(it = targets.begin(); it != targets.end(); ++it) {
        (*it) -> print();
    }
}

void TargetGroup::addTarget(SingleTarget *t)
{
    targets.push_back(t);
}

void TargetGroup::deleteTarget(int id)
{
    std::vector<SingleTarget*>::iterator it;
    for(it = targets.begin(); it != targets.end(); ++it) {
        if ((*it) -> getID() == id) {
            targets.erase(it);
            delete (*it);
            break;
        }
    }
}

void TargetGroup::deleteTarget(SingleTarget *t)
{
    deleteTarget(t -> getID());
}

int TargetGroup::getID()
{
    return id;
}

SingleTarget* TargetGroup::getTarget(size_t index)
{
    if (targets.size() > index) {
        return targets.at(index);
    } else {
        return NULL;
    }
}

SingleTarget* TargetGroup::getTargetByID(int id)
{
    std::vector<SingleTarget*>::iterator it;
    for(it = targets.begin(); it != targets.end(); ++it) {
        if ((*it)!= NULL && (*it) -> getID() == id) {
            return (*it);
        }
    }
    return NULL;
}

size_t TargetGroup::getTargetCount()
{
    return targets.size();
}

TargetGroup* TargetGroup::clone()
{
    TargetGroup* cpy = new TargetGroup(this -> id);
    std::vector<SingleTarget*>::iterator iter;
    for(iter = targets.begin(); iter != targets.end(); ++iter)
    {
        cpy->addTarget((*iter) -> clone());
    }
    return cpy;
}
