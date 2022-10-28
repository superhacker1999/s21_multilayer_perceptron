#include "painter.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    s21::painter w;
    w.show();
    return a.exec();
}
