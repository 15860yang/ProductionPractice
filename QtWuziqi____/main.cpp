#include "GameWindow.h"
#include <QApplication>
#include"snowmanwindow.h"
int main(int argc, char *argv[]){
    QApplication a(argc, argv);

    SnowManWindow w;
    w.show();

    return a.exec();
}
