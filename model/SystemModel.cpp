#include "SystemModel.h"
SystemModel::SystemModel(Matrix &f, Matrix &q):F(f), Q(q)
{
}

SystemModel::SystemModel(const SystemModel &m):F(m.F), Q(m.Q)
{
}

SystemModel::SystemModel(): F(1, 1), Q(1, 1)
{
}

// Destructor
SystemModel::~SystemModel()
{

}

void SystemModel::UpdateModel(Matrix f, Matrix q)
{
	F = f;
	Q = q;
}

void SystemModel::SetF(Matrix f)
{
	F = f;
}

Matrix SystemModel::GetF()
{
	return F;
}

void SystemModel::SetQ(Matrix q)
{
	Q = q;
}

Matrix SystemModel::GetQ()
{
	return Q;
}

SystemModel SystemModel::getModel(SystemModelType type)
{
    Matrix f(9, 9, 0.0), q(9, 9, 0.0);
    q.unit();
    q[2][3] = 5;
	switch(type)
	{
	case SystemModel::CA:			// 匀速直线运动
        f[0][0] = 1;
        f[0][3] = 1;
        f[1][1] = 1;
        f[1][4] = 1;
        f[2][2] = 1;
        f[2][5] = 1;
        f[3][3] = 1;
        f[4][4] = 1;
        f[5][5] = 1;
        f[6][6] = 1;
        f[7][7] = 1;
        f[8][8] = 1;
		break;
	case SystemModel::CV:			// 匀加速运动
        f[0][0] = 1;
        f[0][3] = 1;
        f[0][6] = 0.5;
        f[1][1] = 1;
        f[1][4] = 1;
        f[1][7] = 0.5;
        f[2][2] = 1;
        f[2][5] = 1;
        f[2][8] = 0.5;

        f[3][3] = 1;
        f[3][6] = 1;
        f[4][4] = 1;
        f[4][7] = 1;
        f[5][5] = 1;
        f[6][8] = 1;

        f[6][6] = 1;
        f[7][7] = 1;
        f[8][8] = 1;
		break;
	default:
		break;
	}

    return SystemModel(f, q);
}
