#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include "NumericalCalculation.h"
#include "InterpolationCalculation.h"
#include "TypeTrans.h"
#include "qcustomplot.h"
#include <QtWidgets/QApplication>
#include <QMessageBox>
#include <QLabel>
#include <QPushButton>
#include <QDialog>
using namespace std;
class TypeTrans
{
public:
	TypeTrans();
	vector<double> str2vec(string a);
	double str2doub(string str);
	int str2int(string str);
	double findMax(vector<double> vec);
	double findMin(vector<double> vec);
	vector<vector<double> > nnArray(string str);
	vector<double> vec(string str);
	vector<vector<double> > transpose(vector<double> nvec);
	bool fineMar(vector<vector<double> >a, vector<double> b, int n);//nn矩阵是否与一维向量长度一致
private:
};

