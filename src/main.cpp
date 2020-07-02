#include <QApplication>
#include "panel.hpp"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);    
    Panel p; p.show();



    return a.exec();
}
