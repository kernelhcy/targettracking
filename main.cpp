#include <QtGui/QApplication>
#include <QTextCodec>
#include <QTextStream>
#include "mainwindow.h"
#include "comm.h"
#include "model/singletarget.h"
#include "model/TargetGroup.h"
#include "datasource/targetgenerator.h"

int main(int argc, char *argv[])
{ 
    QApplication a(argc, argv);
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF8"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF8"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF8"));

    MainWindow w;
    w.show();
//    QTextStream out(stdout);
//    TargetGenerator generator(2, 3);
//    generator.go(1);
//    out << "current states : " << endl;
//    std::vector<State> states = generator.getCurrentStates();
//    std::vector<State>::iterator iter;
//    for (iter = states.begin(); iter != states.end(); ++iter) {
//        (*iter).print(out);
//    }
//    generator.go(1);
//    out << "current states : " << endl;
//    states = generator.getCurrentStates();
//    for (iter = states.begin(); iter != states.end(); ++iter) {
//        (*iter).print(out);
//    }

//    generator.go(1);
//    out << "current states : " << endl;
//    states = generator.getCurrentStates();
//    for (iter = states.begin(); iter != states.end(); ++iter) {
//        (*iter).print(out);
//    }
    return a.exec();
}
