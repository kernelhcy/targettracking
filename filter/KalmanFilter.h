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
	KalmanFilter();
	KalmanFilter(SystemModel sm, MeasureModel mm);

    // 析构函数
	virtual ~KalmanFilter();

	SystemModel getSystemModel();

	MeasureModel getMeasureModel();

    // 更新模型
	void UpdateModel(SystemModel sm, MeasureModel mm);

    // 一步状态预测值
	Matrix PriorEstimate(Matrix state);

    // 一步均方误差预测值
	Matrix PriorCovariance(Matrix covariance);

    // 滤波增益
	Matrix CalculateGain(Matrix covariance);

	Matrix CalculateGain(Matrix innoCovariance,Matrix preCovariance);

    // 状态预测值
	Matrix PostEstimate(Matrix gain, Matrix state, Matrix measure);

    // 均方误差预测值
	Matrix PostCovariance(Matrix gain, Matrix covariance);

	Matrix InnovationCovariance(Matrix covariance);

	///量测预测值
	Matrix PreMeasurement(Matrix preState);

private:
	SystemModel systemModel;
	MeasureModel measureModel;

}; // class

KalmanFilter::KalmanFilter()
{
	
}

KalmanFilter::KalmanFilter(SystemModel sm, MeasureModel mm)
{
	systemModel.SetF(sm.GetF());
	systemModel.SetQ(sm.GetQ());
	measureModel.SetH(mm.GetH());
	measureModel.SetR(mm.GetR());
}

KalmanFilter::~KalmanFilter()
{

}

SystemModel KalmanFilter::getSystemModel()
{
	return systemModel;
}

MeasureModel KalmanFilter::getMeasureModel()
{
	return measureModel;
}

void KalmanFilter::UpdateModel(SystemModel sm, MeasureModel mm)
{
	systemModel.SetF(sm.GetF());
	systemModel.SetQ(sm.GetQ());
	measureModel.SetH(mm.GetH());
	measureModel.SetR(mm.GetR());
}

Matrix KalmanFilter::PriorEstimate(Matrix state)
{
    if(systemModel.GetF().colsize() != state.rowsize())
	{
        qCritical() <<"Matrix not match, can't multiply";
	}
	state = systemModel.GetF() * state;
	return state;
}

Matrix KalmanFilter::PriorCovariance(Matrix covariance)
{
    if(systemModel.GetF().colsize() != covariance.rowsize())
	{
        qCritical() <<"Matrix not match, can't multiply";
	}
    covariance = systemModel.GetF() * covariance * (~systemModel.GetF())
								+ systemModel.GetQ();
	return covariance;
}

Matrix KalmanFilter::InnovationCovariance(Matrix covariance)
{
    covariance = measureModel.GetH() * covariance * (~measureModel.GetH())
								+ measureModel.GetR(); //R是否时变
	return covariance;
}

Matrix KalmanFilter::CalculateGain(Matrix covariance)
{
    if(measureModel.GetH().colsize() != covariance.rowsize())
	{
        qCritical() <<"Matrix not match, can't multiply";
	}
    Matrix gain = (covariance * (~measureModel.GetH()))
                    /(measureModel.GetH() * covariance * (~measureModel.GetH())
								+ measureModel.GetR());
	return gain;
}

Matrix KalmanFilter::CalculateGain(Matrix innoCovariance,Matrix preCovariance)
{
    Matrix gain = preCovariance * (~measureModel.GetH()) / innoCovariance;
	return gain;
}

Matrix KalmanFilter::PreMeasurement(Matrix preState)
{
	return measureModel.GetH() * preState;
}

Matrix KalmanFilter::PostEstimate(Matrix gain, Matrix state, Matrix measure)
{
	state = state + gain * (measure - measureModel.GetH() * state);
	return state;
}

Matrix KalmanFilter::PostCovariance(Matrix gain, Matrix covariance)
{
    if( gain.colsize() != measureModel.GetH().rowsize())
	{
        qCritical() <<"Matrix not match! can't multiply";
	}

    Matrix I(gain.rowsize(), gain.rowsize(), 0);
    for(int i = 0; i < gain.rowsize(); i++){
        for(int j = 0; j < gain.rowsize(); j++){
            I(i,j)=0.0;
            if(i==j){
                I(i,j) = 1.0;
            }
        }
    }
    covariance = (I - gain * measureModel.GetH()) * covariance;
    return covariance;
}

#endif // __KALMAN_FILTER__
