/************************************************************************

FileName: IMMFilter.h
Creator: Chen Junliang
Comment: 交互式多模型滤波算法

changelog:
date		version		author			comment
2007/01/01	1.0			Chen Junliang	创建
2008/01/04	1.1			Li Xiangnan		增加注释
************************************************************************/

#if !defined(AFX_IMMFILTER_H__3D0DA75A_B2F5_4549_A779_1CA0F0A7D62D__INCLUDED_)
#define AFX_IMMFILTER_H__3D0DA75A_B2F5_4549_A779_1CA0F0A7D62D__INCLUDED_

#include <vector>
#include <cmath>

#include "KalmanFilter.h"
#include "../model/MeasureModel.h"
#include "../model/SystemModel.h"

#define PI 3.1416

typedef std::vector<SystemModel> SystemModelVector;
typedef std::vector<KalmanFilter> KalmanFilterVector;
typedef std::vector<Matrix> StateVector;
typedef Matrix Measurement;

class IMMFilter
{
public:
	IMMFilter();
	IMMFilter(SystemModelVector smv, MeasureModel mm, Matrix tpm);
	virtual ~IMMFilter();

	//模型交互
	void ModelInteraction(Matrix U, StateVector XE, StateVector PE, Matrix &c, StateVector &X0, StateVector &P0);

	//模型条件滤波
    void ModelConditionedFiltering(StateVector X0, StateVector P0, Measurement Z
                                   , Matrix c, Matrix &A, Matrix &C, StateVector &XE, StateVector &PE);

	//模型概率更新
	void ModelProbabilityUpdate(Matrix A, Matrix c, Matrix C, Matrix &U);

	//状态合并
	void StateCombination(StateVector XE, StateVector PE, Matrix U, Matrix &XXE, Matrix &PPE);

private:
	KalmanFilterVector kalmanFilterVector;
	Matrix transitionProbabilityMatrix;
	int modelNum;
};

IMMFilter::IMMFilter()
{

}

IMMFilter::IMMFilter(SystemModelVector smv, MeasureModel mm, Matrix tpm)
{
	modelNum = smv.size();
	KalmanFilter kf;
	for (int i=0;i<modelNum;i++)
	{
		kf=KalmanFilter(smv[i],mm);
		kalmanFilterVector.push_back(kf);
	}
	transitionProbabilityMatrix = tpm;
}

IMMFilter::~IMMFilter()
{

}

void IMMFilter::ModelInteraction(Matrix U, StateVector XE, StateVector PE, Matrix &c, StateVector &X0, StateVector &P0)
{
	int i,j;
    Matrix UU(modelNum, modelNum, 0);

    for (j = 0; j < modelNum; j++){
        c(1,j) = dot(transitionProbabilityMatrix(c_p,j), U);
	}

    for (i = 0; i < modelNum; i++){
        for(int j = 0; j< modelNum; j++){
            UU(i,j) = transitionProbabilityMatrix(i,j) * U(1,i) / c(1,j);
        }
    }
    for (i = 0; i < modelNum; i++){
        for(j = 0; j < modelNum; j++){
            X0[i] = X0[i] + XE[j] * UU(j + 1, i + 1);
            P0[i] = P0[i] + (PE[j] + (XE[j] - X0[i]) * (~(XE[j]-X0[i]))) * UU(j+1,i+1);
		}
    }
}

void IMMFilter::ModelConditionedFiltering(StateVector X0, StateVector P0
                                          , Measurement Z, Matrix c, Matrix &A
                                          , Matrix &C, StateVector &XE, StateVector &PE)
{
	A=zeros(1,modelNum);
	Matrix miu,S,H,priorEstimate,priorCovariance,gain,postEstiamte,postCovariance;
	Matrix temp;
    for (int i = 0; i < modelNum; i++){
		priorEstimate = kalmanFilterVector[i].PriorEstimate(X0[i]);
		priorCovariance = kalmanFilterVector[i].PriorCovariance(P0[i]);
		gain = kalmanFilterVector[i].CalculateGain(priorCovariance);
		postEstiamte = kalmanFilterVector[i].PostEstimate(gain,priorEstimate,Z);
		postCovariance = kalmanFilterVector[i].PostCovariance(gain,priorCovariance);

		H = kalmanFilterVector[i].getMeasureModel().GetH();
		miu = Z-H*priorEstimate;
        S = H*priorCovariance*(~H); // + D*eye(4);

        A(1,i+1) = exp(-(~miu)*inv(S)*miu/2)/((2*PI)*sqrt(det(S).r(1,1)));
		XE[i]=postEstiamte;
		PE[i]=postCovariance;
	}
	C = dot(A,c);
}

void IMMFilter::ModelProbabilityUpdate(Matrix A, Matrix c, Matrix C, Matrix &U)
{
	//	U=zeros(1,modelNum);
	for (int i=0;i<modelNum;i++)
	{
		U.r(1,i+1) = A.r(1,i+1)*c.r(1,i+1)/C.r(1,1);
	}
}

void IMMFilter::StateCombination(StateVector XE, StateVector PE, Matrix U, Matrix &XXE, Matrix &PPE)
{
	for (int i=0;i<modelNum;i++)
	{
		XXE = XXE + XE[i]*U.r(1,i+1);
	}
}

#endif // !defined(AFX_IMMFILTER_H__3D0DA75A_B2F5_4549_A779_1CA0F0A7D62D__INCLUDED_)
