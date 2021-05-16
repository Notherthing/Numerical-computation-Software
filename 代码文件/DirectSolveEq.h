#pragma once
#include<iostream>
#include<math.h>
#include<iomanip>
#include<string>
#include<vector>
using namespace std;
class DirectSolveEq
{
public:
	DirectSolveEq();
	string Gauss(vector<vector<double> >a, vector<double> b, int n);
	string lie_Gauss(vector<vector<double> >a, vector<double> b, int n);
	string Chasing_method(vector<vector<double> >a, vector<double>d, int n);
	string Square(vector<vector<double> >a, vector<double>b, int n);
};

