#ifndef __COMM_H
#define __COMM_H

#include "matrixtcl/cmatrix"
#include <vector>

typedef techsoft::matrix<double> Matrix;

void printf_matrix(const Matrix &m);

class TargetGroup;
// 集群数据
extern std::vector<TargetGroup*> *g_groups;

#endif // COMM_H
