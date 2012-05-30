#include "State.h"
#include <stdio.h>
#include <QDebug>

State::State(double x, double y, double z, double xx, double yy, double zz
             , double xxx, double yyy, double zzz, int t):m(9, 1, 0.0)
{
    m[0][0] = x;
    m[1][0] = y;
    m[2][0] = z;
    m[3][0] = xx;
    m[4][0] = yy;
    m[5][0] = zz;
    m[6][0] = xxx;
    m[7][0] = yyy;
    m[8][0] = zzz;
	time = t;

    // eat the memory...
    a[125] = 'a';
    a[2023] = 'a';
}

State::State(const State &s):m(s.m), time(s.time)
{
}


Matrix State::getPostion()
{
    Matrix newm(3, 1, 0.0);
    newm[0][0] = m[0][0];
    newm[1][0] = m[1][0];
    newm[2][0] = m[2][0];
	return newm;
}
Matrix State::geSpeed()
{
    Matrix newm(3, 1, 0.0);
    newm[0][0] = m[3][0];
    newm[1][0] = m[4][0];
    newm[2][0] = m[5][0];
	return newm;
}
Matrix State::getAcceleration()
{
    Matrix newm(3, 1, 0.0);
    newm[0][0] = m[6][0];
    newm[1][0] = m[7][0];
    newm[2][0] = m[8][0];
	return newm;
}

void State::print()
{
    qDebug() << "\t" << "\t"<< time << "\t"
        << m[0][0] << "\t" << m[1][0] << "\t" << m[2][0] << "\t"
        << m[3][0] << "\t" << m[4][0] << "\t" << m[5][0] << "\t"
        << m[6][0] << "\t" << m[7][0] << "\t" << m[8][0] << "\t";
}
