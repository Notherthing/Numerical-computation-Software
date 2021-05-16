#include "CharacteristicValue.h"
#include<iostream>
#include<math.h>
#include<iomanip>
#include<string>
#include<vector>

using namespace std;

CharacteristicValue::CharacteristicValue()
{
	cout << "class is been created successfully" << endl;
}

string CharacteristicValue::Iter_min(vector<vector<double>> Mat, vector<vector<double>> u, double epsilon)
{
	int size = Mat[0].size();
	string result = "Characteristic value:\n";
	bool t = 0;
	double res[2];
	while (true) {
		t = !t;
		for (int i = 0; i < size; i++) {
			//清除旧的迭代结果，以消除误差
			u[i][t] = 0;
			for (int j = 0; j < size; j++) {
				//记录新的迭代结果
				u[i][t] += u[j][!t] * Mat[i][j];
			}
		}
		res[t] = u[0][t] / u[0][!t];

		if (res[1] - res[0] < epsilon && res[0] - res[1] < epsilon) break;
	}
	double minVal = 1e100;
	for (int i = 0; i < size; i++) {
		if (u[i][t] < minVal) minVal = u[i][t];
	}
	for (int i = 0; i < size; i++) {
		u[i][t] /= minVal;
	}
	minVal = 1e100;
	for (int i = 0; i < size; i++) {
		if (u[i][!t] < minVal) minVal = u[i][!t];
	}
	for (int i = 0; i < size; i++) {
		u[i][!t] /= minVal;
	}
	result += to_string(res[t]) + "\n\n" + "Characteristic vector:\n";
	for (int i = 0; i < size; i++)
		result += to_string(u[i][t]) + " ";

	return result;
}

string CharacteristicValue::Iter_max(vector<vector<double>> Mat, vector<vector<double>> u, double epsilon)
{
	int size = Mat[0].size();
	string result = "Characteristic value:\n";
	bool t = 0;
	double res[2];
	while (true) {
		t = !t;
		for (int i = 0; i < size; i++) {
			//清除旧的迭代结果，以消除误差
			u[i][t] = 0;
			for (int j = 0; j < size; j++) {
				//记录新的迭代结果
				u[i][t] += u[j][!t] * Mat[i][j];
			}
		}
		res[t] = u[0][t] / u[0][!t];

		if (res[1] - res[0] < epsilon && res[0] - res[1] < epsilon) break;
	}
	double maxVal = -1e100;
	for (int i = 0; i < size; i++) {
		if (u[i][t] > maxVal) maxVal = u[i][t];
	}
	for (int i = 0; i < size; i++) {
		u[i][t] /= maxVal;
	}
	maxVal = -1e100;
	for (int i = 0; i < size; i++) {
		if (u[i][!t] > maxVal) maxVal = u[i][!t];
	}
	for (int i = 0; i < size; i++) {
		u[i][!t] /= maxVal;
	}
	result += to_string(res[t]) + "\n\n" + "Characteristic value:\n";
	for (int i = 0; i < size; i++)
		result += to_string(u[i][t]) + " ";
	return result;
}