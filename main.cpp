#include "mainwindow.h"
int main(int argc, char *argv[])
{
    QApplication CuatroEnLinea(argc, argv);
    MainWindow mw(&CuatroEnLinea);
    mw.show();

    return CuatroEnLinea.exec();
}
