#include "KalmanFilter.h"

KalmanFilter::KalmanFilter(SystemModel sm, MeasureModel mm)
    : systemModel(sm), measureModel(mm)
{
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

void KalmanFilter::setModel(SystemModel sm, MeasureModel mm)
{
    systemModel.SetF(sm.GetF());
    systemModel.SetQ(sm.GetQ());
    measureModel.SetH(mm.GetH());
    measureModel.SetR(mm.GetR());
}

Matrix KalmanFilter::estimate()
{
    if(systemModel.GetF().colsize() != state.rowsize())
    {
        qCritical() <<"Matrix not match, can't multiply";
    }
    // 计算预测状态
    this->state = systemModel.GetF() * state;
    // 计算预测误差协方差
    this->covariance = systemModel.GetF() * this->covariance * (~systemModel.GetF()) + systemModel.GetQ();
    return this->state;
}

void KalmanFilter::updateByMeasure(Matrix measure)
{
    // 计算增益
    gain = (covariance * (~measureModel.GetH()))
                        /(measureModel.GetH() * covariance * (~measureModel.GetH())
                                    + measureModel.GetR());
    // 更新状态
    state = state + gain * (measure - measureModel.GetH() * state);

    // 更新误差协方差阵
    Matrix I(gain.rowsize(), gain.rowsize());
    for(size_t i = 0; i < gain.rowsize(); i++){
        for(size_t j = 0; j < gain.rowsize(); j++){
            I(i,j)=0.0;
            if(i==j){
                I(i,j) = 1.0;
            }
        }
    }
    covariance = (I - gain * measureModel.GetH()) * covariance;
}

