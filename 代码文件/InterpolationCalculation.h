#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "TypeTrans.h"
using namespace std;
class InterpolationCalculation
{
public:
	InterpolationCalculation();
	vector<double> poly_add(vector<double> a, vector<double> b);
	//用于处理多项式相加,同幂次系数相加，结果存于vector中
	vector<double> lagrange_poly(vector<double> x, vector<double> y);
	//通过(x,y)的所有点，得到拉格朗日函数的每个xn前的系数
	string lagrange_str(vector<double> coefficient);
	//通过上面的得到的系数向量，得到拉格朗日函数的string
	double value_ans(double x, vector<double>poly);
	//通过系数向量，与L(x)中的x的参数，得到估值结果
	double newton(double p, vector<double> x, vector<double> y);
	//通过牛顿插值法，求估计值
	string piecewise(int degree, double p, vector<double> x, vector<double> y);
	//通过分段插值法，求估计值
	string piecewise_poly(int degree, double p, vector<double> x, vector<double> y);
private:

};

