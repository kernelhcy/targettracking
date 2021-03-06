// kalmanfilter.h
//  

#ifndef __KALMAN_FILTER__
#define __KALMAN_FILTER__

/** 
KalmanFilter类，为卡尔曼滤波算法基类
*/

#include "../matrixtcl/cmatrix"
#include "../model/MeasureModel.h"
#include "../model/SystemModel.h"
#include <QDebug>

class KalmanFilter
{
protected:

public:
    // 构造函数
	KalmanFilter(SystemModel sm, MeasureModel mm);
    KalmanFilter();

    // 析构函数
	virtual ~KalmanFilter();

	SystemModel getSystemModel();
	MeasureModel getMeasureModel();
    // 设置模型
    void setModel(SystemModel sm, MeasureModel mm);


    // 一步状态预测值
    Matrix estimate();

    // 使用测量值更新状态和误差
    void updateByMeasure(Matrix measure);

    Matrix getState() const{ return this->state; }
    Matrix getCovariance() const{ return this->covariance; }
    Matrix getGain() const{ return this->gain; }

    void setGroupId(int grpid) { groupId = grpid; }
    void setTargetId(int targetid) {targetId = targetid;}
    int getGroupId() const { return groupId; }
    int getTargetId() const { return targetId; }

    void setState(Matrix m){ state = m; }
private:
    // 对应的集群和目标id
    int groupId;
    int targetId;

	SystemModel systemModel;
	MeasureModel measureModel;

    Matrix state;       // 当前状态
    Matrix covariance;  // 误差的协方差阵
    Matrix gain;        // 增益 

    void init();
}; // class

#endif // __KALMAN_FILTER__
