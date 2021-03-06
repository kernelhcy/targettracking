#ifndef TARGETGENERATOR_H
#define TARGETGENERATOR_H

#include "../model/TargetGroup.h"
#include <vector>
#include <QFile>
#include <QString>
#include <QVector>
#include "../model/State.h"
#include "../model/TargetState.h"


//
// 目标数据读取器。从文件中读取。
//
class TargetDataReader
{
public:
    TargetDataReader(QString filePath);
    ~TargetDataReader();

    // 获取下一时刻所有目标的状态
    std::vector<State> getNextStates();
private:
    QString filePath;
    QFile file;
    QVector<QString> dataVector;
    QVector<QVector<QString>* > allDataVector;

    State createStateFromLine(QString line);

};

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
    // 获取当前所有目标的状态。模拟数据关联算法输出的数据
    // 返回的是一个vector，不是vector指针。
    //
    std::vector<TargetState> getCurrentStates();

private:
    bool isFromFile;
    std::vector<TargetGroup*> groups;
    int targetInGroupNumber;
    int groupNumber;

    int skyGroupNumber;         // 空中集群数目
    int groundGroupNumber;      // 地面集群数目

    TargetDataReader *dateReader;

    void initGroups();
    TargetGroup* createGroup(int id, State initState, int targetNum);
};

#endif // TARGETGENERATOR_H
