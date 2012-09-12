#pragma once
#include "../comm.h"

/*
* 系统（目标）的运动模型
* 表示为三维模型。
*
*/
class SystemModel
{
public:
	// 运动模型的类型
	typedef enum{
		CA,			// 匀速直线模型 
		CV			// 匀加速直线模型
	}SystemModelType;

	/// Constructor
	SystemModel(Matrix& f, Matrix& q);
    SystemModel(const SystemModel &m);
    SystemModel();

	/// Destructor
	virtual ~SystemModel();

	//更新模型
    void UpdateModel(Matrix f, Matrix q);

	//设置状态转移矩阵
    void SetF(Matrix f);

	//获得状态转移矩阵
	Matrix GetF();

	//设置状态噪声协方差
    void SetQ(Matrix q);

	//获得状态噪声协方差
	Matrix GetQ();

	/*
	* 静态方法。获取一个模型实例
	* @param type 模型类型
	*/
    static SystemModel getModel(SystemModelType type);
private:
	Matrix F;	// 状态转移矩阵。
	Matrix Q;	// 协方差矩阵

};

