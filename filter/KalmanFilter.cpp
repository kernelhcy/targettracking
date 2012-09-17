#include "KalmanFilter.h"
#include <QDebug>

KalmanFilter::KalmanFilter(SystemModel sm, MeasureModel mm)
    :  groupId(0), targetId(0), systemModel(sm), measureModel(mm), state(9, 1, 0.0)
    , covariance(9, 9, 0.0), gain(9, 9, 0.0)
{
    init();
}

KalmanFilter::KalmanFilter()
    :  groupId(0), targetId(0), systemModel(SystemModel::getModel(SystemModel::CA))
    , measureModel(MeasureModel::getModel()), state(9, 1, 0.0), covariance(9, 9, 0.0), gain(9, 9, 0.0)
{
    init();
}

void KalmanFilter::init()
{
    // 初始化为单位矩阵
    covariance.unit();
    gain.unit();
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
    // 计算预测状态
    this->state = systemModel.GetF() * state;
    // 计算预测误差协方差
    this->covariance = systemModel.GetF() * (this->covariance) * (~systemModel.GetF()) + systemModel.GetQ();
//    qDebug() << "covariance: ";
//    printf_matrix(covariance);
    return this->state;
}

void KalmanFilter::updateByMeasure(Matrix measure)
{
    // 计算增益
    Matrix a = covariance * (~measureModel.GetH());
    Matrix b = measureModel.GetH() * covariance * (~measureModel.GetH()) + measureModel.GetR();
    gain = a / b;
//    qDebug() << "gain: ";
//    printf_matrix(gain);

    // 更新状态
    state = state + gain * (measure - measureModel.GetH() * state);

    // 更新误差协方差阵
    Matrix I(9, 9, 0.0);
    I.unit();
    covariance = (I - gain * measureModel.GetH()) * covariance;
}

