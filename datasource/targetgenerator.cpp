#include "targetgenerator.h"
#include "../model/singletarget.h"
#include "../model/SystemModel.h"
#include <math.h>
#include <QtGlobal>
#include <QTextStream>
#include <QStringList>
#include <QSettings>
#include <QDebug>

static State states[30] = {
    // 地面集群初始化状态
    State(300, -30, 0, 50, 105, 0,    1, 1, 0, 0),
    State(300, -30, 0, 5, 95, 0,      2, 3, 0, 0),
    State(300, -30, 0, 150, 85, 0,    1, -2, 0, 0),
    State(300, -30, 0, 50, 75, 0,     2, 1, 0, 0),
    State(300, -30, 0, 40, 65, 0,     3, 2, 0, 0),
    State(300, -30, 0, 30, 55, 0,     -1, 1, 0, 0),
    State(300, -30, 0, 20, 45, 0,     2, 2, 0, 0),
    State(300, -30, 0, 10, 35, 0,     3, 1, 0, 0),
    State(300, -30, 0, 140, 25, 0,    -2, 1, 0, 0),
    State(300, -30, 0, -130, 15, 0,   3, 2, 0, 0),
    State(300, -30, 0, 120, 25, 0,   2, 2, 0, 0),
    State(300, -30, 0, 110, 45, 0,   -1, 3, 0, 0),
    State(300, -30, 0, 100, 245, 0,   3, -2, 0, 0),
    State(300, -30, 0, -50, 175, 0,   2, -1, 0, 0),
    State(300, -30, 0, -30, 135, 0,  3, 2, 0, 0),
    // 空中集群初始化状态
    State(300, 0, 0, 50, 205, 0, 8, -5, 0, 0),
    State(300, 0, 0, 50, 205, 0, 8, -5, 0, 0),
    State(300, 0, 0, 50, 205, 0, 8, -5, 0, 0),
    State(300, 0, 0, 50, 205, 0, 8, -5, 0, 0),
    State(300, 0, 0, 50, 205, 0, 8, -5, 0, 0),
    State(300, 0, 0, 50, 205, 0, 8, -5, 0, 0),
    State(300, 0, 0, 50, 205, 0, 8, -5, 0, 0),
    State(300, 0, 0, 50, 205, 0, 8, -5, 0, 0),
    State(300, 0, 0, 50, 205, 0, 8, -5, 0, 0),
    State(300, 0, 0, 50, 205, 0, 8, -5, 0, 0),
    State(300, 0, 0, 50, 205, 0, 8, -5, 0, 0),
    State(300, 0, 0, 50, 205, 0, 8, -5, 0, 0),
    State(300, 0, 0, 50, 205, 0, 8, -5, 0, 0),
    State(300, 0, 0, 50, 205, 0, 8, -5, 0, 0),
    State(300, 0, 0, 50, 205, 0, 8, -5, 0, 0)
};

TargetGenerator::TargetGenerator(int groupNum, int targetInGroupNum, int skyGroupNumber, int groundGroupNumber)
    : targetInGroupNumber(targetInGroupNum), groupNumber(groupNum), groups(), isFromFile(false), dateReader(NULL)
    , skyGroupNumber(skyGroupNumber), groundGroupNumber(groundGroupNumber)
{
    QSettings settings(SETTING_ORGANIZATION, SETTING_APPLICATION);
    if (settings.value(SETTING_DATA_SOURCE_KEY, SETTING_DATA_SOURCE_AUTO_GENERATE) == SETTING_DATA_SOURCE_FROM_FILE) {
        isFromFile = true;
        dateReader = new TargetDataReader(settings.value(SETTING_FILE_PATH_KEY, "").toString());
    }
    initGroups();
}
TargetGenerator::~TargetGenerator()
{
    delete dateReader;
    std::vector<TargetGroup*>::iterator iter;
    for ( iter = groups.begin(); iter != groups.end(); ++iter){
        delete (*iter);
    }
}

void TargetGenerator::go(int time)
{
    if (isFromFile) {
        // 从文件读取目标数据
        std::vector<State> states = dateReader -> getNextStates();
        TargetGroup *grp = groups[0];   //只有一个集群
        SingleTarget *target;
        for (size_t i = 0; i < states.size(); ++i) {
            target = grp -> getTarget(i);
            if (target) {
                target -> addState(states[i]);
            }
        }
    } else {
        // 自动生成的数据需要计算
        std::vector<TargetGroup*>::iterator iter;
        for ( iter = groups.begin(); iter != groups.end(); ++iter){
            (*iter) -> go(time);
        }
    }
}

std::vector<TargetGroup*>* TargetGenerator::getGroups()
{
    return &groups;
}

void TargetGenerator::initGroups()
{
    int groupId = 1;
    if (isFromFile) {
        // 从文件读取目标数据
        std::vector<State> states = dateReader -> getNextStates();
        TargetGroup *grp = new TargetGroup(groupId * 1000); // 所有的目标放到一个集群中
        SingleTarget *target;
        for (size_t i = 0; i < states.size(); ++i) {
            target = new SingleTarget(groupId * 1000 + i, SystemModel::getModel(SystemModel::CV), states[i]);
            grp -> addTarget(target);
        }
        groups.push_back(grp);
    } else {
        // 自动生成目标数据
        // 地面集群
        for (int i = 0; i < groundGroupNumber; ++i) {
            int index = qrand() % 15;
            State initState = states[index];
            initState.setPositionX(groupId * 300);
            TargetGroup * grp = createGroup(groupId * 1000, initState, targetInGroupNumber);
            groups.push_back(grp);
            ++groupId;
        }

        // 空中集群
        for (int i = 0; i < skyGroupNumber; ++i) {
            int index = qrand() % 15;
            State initState = states[index + 15];
            initState.setPositionX(groupId * 300);
            TargetGroup * grp = createGroup(groupId * 1000, initState, targetInGroupNumber);
            groups.push_back(grp);
            ++groupId;
        }
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

std::vector<TargetState> TargetGenerator::getCurrentStates()
{
    std::vector<TargetState> states;
    std::vector<TargetGroup*>::iterator iter;
    State *s;
    TargetGroup *grp;
    SingleTarget *target;
    TargetState tState;
    for ( iter = groups.begin(); iter != groups.end(); ++iter){
        grp = (*iter);
        int targetCount = grp -> getTargetCount();
        for (int i = 0; i < targetCount; ++i) {
            target = grp -> getTarget(i);
            s = target -> getCurrState();
            tState.groupId = grp->getID();
            tState.targetId = target->getID();
            tState.state = *s;
            tState.time = s->getTime();
            states.push_back(tState);
        }
    }
    return states;
}

//************************  TargetDataReader *******************************************
TargetDataReader::TargetDataReader(QString path): filePath(path), file(path)
{
    qDebug() << "读取文件数据：\n";
    file.open(QIODevice::ReadOnly);
    QTextStream stream(&file);
    QString line;
    while(true) {
        line = stream.readLine();
        if (line.isNull()) {
            break;
        }
        dataVector.push_back(line);
        qDebug() << line;
    };

    file.close();
}

TargetDataReader::~TargetDataReader()
{

}

// 获取下一时刻所有目标的状态
std::vector<State> TargetDataReader::getNextStates()
{
    std::vector<State> re;
    if (dataVector.size() > 0) {
        QString line = dataVector.front();
        State s = createStateFromLine(line);
        if (re.size() == 0) {
            re.push_back(s);
            dataVector.pop_front();
        } else {
            State preState = re.back();
            if (preState.getTime() == s.getTime()) {
                re.push_back(s);
                dataVector.pop_front();
            }
        }
    }
    return re;
}

State TargetDataReader::createStateFromLine(QString line)
{
    QStringList stringList = line.split("\t");
    float id, x, y, vx, vy;
    if (stringList.size() < 5) {
        qDebug() << "数据出错！" << line;
        return State();
    }
    QString tmp = stringList.at(0);
    id = tmp.toFloat();
    tmp = stringList.at(1);
    x = tmp.toFloat();
    tmp = stringList.at(2);
    y = tmp.toFloat();
    tmp = stringList.at(3);
    vx = tmp.toFloat();
    tmp = stringList.at(4);
    vy = tmp.toFloat();
    State s;
    s.setTime((int)(id * 1000));
    s.setPositionX(x * 30);
    s.setPositionY(y * 200);
    s.setPositionZ(0);
    s.setSpeedX(vx * 30);
    s.setSpeedY(vy * 200);
    s.setSpeedZ(0);
    s.setAcceleratinX(0).setAcceleratinY(0).setAcceleratinZ(0);

    return s;
}
