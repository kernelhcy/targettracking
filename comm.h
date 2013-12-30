#ifndef __COMM_H
#define __COMM_H

#include "matrixtcl/cmatrix"
#include <vector>

typedef techsoft::matrix<double> Matrix;

void printf_matrix(const Matrix &m);

// 目标集群
class TargetGroup;
extern std::vector<TargetGroup*> *g_groups;
extern std::vector<TargetGroup*> *g_filted_groups;       // 滤波后的集群状态

// 滤波器
class KalmanFilter;
extern std::vector<KalmanFilter*> *g_filters;

extern bool isTracking;         // 是否正在进行跟踪。

#define SETTING_ORGANIZATION                "sslib"
#define SETTING_APPLICATION                 "targettracking"
#define SETTING_GROUP_NUMBER_KEY            "group number"         // 集群数
#define SETTING_GROUP_TARGET_NUMBER_KEY     "group target number"  // 集群中目标数
#define SETTING_SKY_TARGET_NUMBER_KEY       "sky target number"    // 空中集群数目
#define SETTING_GROUND_TARGET_NUMBER_KEY    "ground target number" // 地面集群数目

#define SETTING_TRANSMIT_IP                 "ip"

#define SETTING_KALMAN_FILTER_KEY           "kalman filter"
#define SETTING_EKALMAN_FILTER_KEY          "ekalman filter"
#define SETTING_UKALMAN_FILTER_KEY          "ukalman filter"
#define SETTING_PARTICAL_FILTER_KEY         "partical filter"

#define SETTING_FILE_PATH_KEY               "file path"             // 数据问文件路径

#define SETTING_DATA_SOURCE_KEY             "data source"           // 目标数据源类型
#define SETTING_DATA_SOURCE_FROM_FILE       1                       // 从文件读取目标数据
#define SETTING_DATA_SOURCE_AUTO_GENERATE   2                       // 程序自动生成目数据
#endif // COMM_H
