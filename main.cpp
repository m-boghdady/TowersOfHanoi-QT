#include "toh_animation.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TOH_Animation w;
    w.show();
    return a.exec();
}
