#include "comm.h"
#include <QTextStream>
void printf_matrix(const Matrix &m)
{
    size_t colno, rowno;
    colno = m.colno();
    rowno = m.rowno();
    QTextStream out(stdout);
    for(size_t i = 0; i < rowno; ++i){
        for(size_t j = 0; j < colno; ++j){
            out << m[i][j] << "\t";
        }
        out << endl;
    }
    out << endl;
}

std::vector<TargetGroup*> *g_groups = NULL;
bool isTracking = false;
