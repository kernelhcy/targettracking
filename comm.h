#ifndef __COMM_H
#define __COMM_H

#include "matrixtcl/cmatrix"
#include <vector>

typedef techsoft::matrix<double> Matrix;

void printf_matrix(const Matrix &m);

class TargetGroup;
// 集群数据
extern std::vector<TargetGroup*> *g_groups;
extern bool isTracking;         // 是否正在进行跟踪。

#define SETTING_ORGANIZATION                "sslib"
#define SETTING_APPLICATION                 "targettracking"
#define SETTING_GROUP_NUMBER_KEY            "group number"         // 集群数
#define SETTING_GROUP_TARGET_NUMBER_KEY     "group target number"  // 集群中目标数
#define SETTING_SKY_TARGET_NUMBER_KEY       "sky target number"    // 空中集群数目
#define SETTING_GROUND_TARGET_NUMBER_KEY    "ground target number" // 地面集群数目

#endif // COMM_H
