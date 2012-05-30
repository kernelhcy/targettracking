#pragma once
/*
* 表示目标的运动状态。
* 运动状态包括位置坐标（x,y,z），速度(x', y', z')和加速度（x'', y'', z''）
* 运动的方向由三个分量求得。
* 用矩阵进行保存，保存的格式为[x,y,z,x',y',z',x'',y'',z'']'
*/
#include "../comm.h"

class State
{
public:
    State():m(9, 1, 0.0){}
	State(double x, double y, double z, double xx, double yy, double zz
		, double xxx, double yyy, double zzz, int t);

	State(const State &s);

	//返回位置，速度和加速度矩阵
    Matrix getPostion();
    Matrix geSpeed();
    Matrix getAcceleration();

	//返回位置的xyz坐标
    double getPositionX(){	return m[0][0]; }
    double getPositionY(){	return m[1][0]; }
    double getPositionZ(){	return m[2][0]; }

	//返回速度的xyz分量
    double getSpeedX(){	return m[3][0]; }
    double getSpeedY(){	return m[4][0]; }
    double getSpeedZ(){	return m[5][0]; }

	//返回加速度的xyz分量
    double getAcceleratinX(){	return m[6][0]; }
    double getAcceleratinY(){	return m[7][0]; }
    double getAcceleratinZ(){	return m[8][0]; }

	//设置位置
    State& setPositionX(double v){	m[0][0] = v; return *this; }
    State& setPositionY(double v){	m[1][0] = v; return *this; }
    State& setPositionZ(double v){	m[2][0] = v; return *this; }
	//设置速度
    State& setSpeedX(double v){	m[3][0] = v; return *this; }
    State& setSpeedY(double v){	m[4][0] = v; return *this; }
    State& setSpeedZ(double v){	m[5][0] = v; return *this; }
	//设置加速度
    State& setAcceleratinX(double v){	m[6][0] = v; return *this; }
    State& setAcceleratinY(double v){	m[7][0] = v; return *this; }
    State& setAcceleratinZ(double v){	m[8][0] = v; return *this; }

    Matrix getData(){ return m; }
    void setData(Matrix &newm) { m = newm; }

    int getTime(){ return time; }
    void setTime(int value) { time = value; }

    void print();
private:
    Matrix m;
	int time;
    char a[2048]; // I think you understand this... ^v^
};
