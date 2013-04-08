#include <stdlib.h>
#include <stdio.h>
#include <QDebug>
#include "targettracker.h"
#include<Winsock2.h>
#pragma comment(lib,"ws2_32.lib")


TargetTracker::TargetTracker(): filters(), filtedTargetGrps(), filtedTargetGrpsArray()
{
}

TargetTracker::~TargetTracker()
{
    std::map<int, KalmanFilter*>::const_iterator iter1;
    for(iter1 = filters.begin(); iter1 != filters.end(); ++iter1){
        delete (iter1 -> second);
    }

    std::map<int, TargetGroup*>::const_iterator iter;
    for (iter = filtedTargetGrps.begin(); iter != filtedTargetGrps.end(); ++iter)
    {
        delete (iter -> second);
    }
}

void TargetTracker::tracking(std::vector<TargetState> states)
{
    std::vector<TargetState>::const_iterator iter;
    TargetState tState;
    KalmanFilter *filter;
    SingleTarget *target;   
    qDebug() << "测量值：";

    for (iter = states.begin(); iter != states.end(); ++iter)
    {
        tState = *iter;
        tState.state.print();

        filter = findFilter(tState.groupId, tState.targetId);
        target = findTarget(tState.groupId, tState.targetId);
        if (target == NULL) continue;
        if (filter == NULL) continue;
        if (target->getStateCount() == 0) {
            // 第一次获取目标的状态，直接保存，不做任何计算。
            target->addState(tState.state);
            filter->setState(tState.state.getData());
            continue;
        }
        //计算一步预测值
        Matrix matrix = filter->estimate();
        // 根据测量值更新预测数据
        filter->updateByMeasure(tState.state.getData());
        State s;
        s.setData(matrix);
        s.setTime(tState.time);
        target->addState(s);
    }

    initMessage();
    printTargetGroups();
}

KalmanFilter* TargetTracker::findFilter(int grpId, int targetId)
{
    KalmanFilter *filter = NULL;
    filter = filters[grpId * 100000 + targetId];
    if (filter == NULL) {
        filter = new KalmanFilter();    // 使用默认的运动模型
        filter->setGroupId(grpId);
        filter->setTargetId(targetId);
        filters[grpId * 100000 + targetId] = filter;
    }
    return filter;
}

SingleTarget* TargetTracker::findTarget(int grpId, int targetId)
{
    TargetGroup *tg = NULL;
    tg = filtedTargetGrps[grpId];
    if (tg == NULL) {
        // 没有找到对应的集群，创建一个新的集群.
        tg = new TargetGroup(grpId);
        filtedTargetGrps[grpId] = tg;
        filtedTargetGrpsArray.push_back(tg);
    }
    SingleTarget *t = tg->getTargetByID(targetId);
    if (t == NULL) {
        // 没有找到对应的目标，创建一个目标.
        t = new SingleTarget(targetId);
        tg->addTarget(t);
    }
    return t;
}

void TargetTracker::printTargetGroups()
{
    qDebug() << "预测值：";
    TargetGroup *tg = NULL;
    std::map<int, TargetGroup*>::const_iterator iter;
    for (iter = filtedTargetGrps.begin(); iter != filtedTargetGrps.end(); ++iter)
    {
        tg = (iter -> second);
        SingleTarget *t;
        for (size_t i = 0; i < tg->getTargetCount(); ++i) {
            t = tg->getTarget(i);
            t->getCurrState()->print();
        }
    }
    closesocket(sockClient);
    WSACleanup();
}

void TargetTracker::initMessage()
{
    char sendbuffer [10000]="a ";
    char NumtoChar [30];
    NumtoChar[0] = 0;
    State* s;

    itoa (filtedTargetGrpsArray.size(), NumtoChar, 10);
    strcat (NumtoChar, " ");
    strcat(sendbuffer, NumtoChar);

    for(int i=0;i<filtedTargetGrpsArray.size();i++)
    {
        s = filtedTargetGrpsArray[i]->getTarget(0)->getCurrState();
        itoa (s->getPositionX(), NumtoChar, 10);
        strcat (NumtoChar, " ");
        strcat(sendbuffer, NumtoChar);
        itoa (s->getPositionY(), NumtoChar, 10);
        strcat (NumtoChar, " ");
        strcat(sendbuffer, NumtoChar);
        itoa (s->getPositionZ(), NumtoChar, 10);
        strcat (NumtoChar, " ");
        strcat(sendbuffer, NumtoChar);
        itoa (s->getSpeedX(), NumtoChar, 10);
        strcat (NumtoChar, " ");
        strcat(sendbuffer, NumtoChar);
        itoa (s->getSpeedY(), NumtoChar, 10);
        strcat (NumtoChar, " ");
        strcat(sendbuffer, NumtoChar);
        itoa (s->getSpeedZ(), NumtoChar, 10);
        strcat (NumtoChar, " ");
        strcat(sendbuffer, NumtoChar);
        itoa (s->getAcceleratinX(), NumtoChar, 10);
        strcat (NumtoChar, " ");
        strcat(sendbuffer, NumtoChar);
        itoa (s->getAcceleratinY(), NumtoChar, 10);
        strcat (NumtoChar, " ");
        strcat(sendbuffer, NumtoChar);
        itoa (s->getAcceleratinZ(), NumtoChar, 10);
        strcat (NumtoChar, " ");
        strcat(sendbuffer, NumtoChar);
        itoa (s->getTime(), NumtoChar, 10);
        strcat (NumtoChar, " ");
        strcat(sendbuffer, NumtoChar);
    }
    sentMessage(sendbuffer);
}

void TargetTracker::sentMessage(char* sendBuf)
{
    send(sockClient,sendBuf,strlen(sendBuf)+1,0);
    //int kk = strlen(sendBuf);
    //char tmp[100000];
    //recv(sockClient,tmp,100000,0);
    //kk = strlen(tmp);
    //printf ("%s\n", tmp);
    //qDebug() << tmp;
}

void TargetTracker::initSocketClient()
{
    WORD wVersionRequested;
    WSADATA wsaData;
    int err;
    wVersionRequested = MAKEWORD(1,1);
    err = WSAStartup(wVersionRequested,&wsaData);
    if(err!=0)
    {
        return;
    }
    if(LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) != 1 )
    {
        WSACleanup();
        return;
    }
    sockClient = socket(AF_INET,SOCK_STREAM,0);
    SOCKADDR_IN addrSrv;
    addrSrv.sin_addr.S_un.S_addr = inet_addr("166.111.82.80");
    addrSrv.sin_family = AF_INET;
    addrSrv.sin_port = htons(6000);
    connect(sockClient,(SOCKADDR*)&addrSrv,sizeof(SOCKADDR));
}
