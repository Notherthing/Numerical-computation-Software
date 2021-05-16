#pragma once
#include<iostream>
#include<math.h>
#include<iomanip>
#include<string>
#include<vector>

using namespace std;

class CharacteristicValue
{
public:
	CharacteristicValue();
	string Iter_min(vector<vector<double>> Mat, vector<vector<double>> u, double epsilon);
	string Iter_max(vector<vector<double>> Mat, vector<vector<double>> u, double epsilon);
};

