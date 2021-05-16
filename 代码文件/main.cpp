#include "NumericalCalculation.h"
#include "InterpolationCalculation.h"
#include "TypeTrans.h"
#include "qcustomplot.h"
#include <QtWidgets/QApplication>
#include <string>
#include <fstream>

int main(int argc, char *argv[])
{
    string temp;
    ifstream readFile("athourity.txt");
    readFile >> temp;
    readFile.close();
    if (temp == "okk")
    {
        QApplication a(argc, argv);
        NumericalCalculation w;
        w.show();
        return a.exec();
    }
    return -1;
}
