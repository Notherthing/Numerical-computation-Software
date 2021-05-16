#pragma once
#include<iostream>
#include<math.h>
#include<iomanip>
#include<string>
#include<vector>
using namespace std;
class IterationSolve
{
public:
	IterationSolve();
	string Jacobi(vector<vector<double> >a, vector<double> b, double e);
	string GS(vector<vector<double>> a, vector<double> b, double e);
	string SOR(vector<vector<double> >a, vector<double> b, double e, double w);
};

