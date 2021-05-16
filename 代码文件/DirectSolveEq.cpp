#include "DirectSolveEq.h"
#include<iostream>
#include<math.h>
#include<iomanip>
#include<string>
#include<vector>
using namespace std;
DirectSolveEq::DirectSolveEq()
{
	cout << "class is been created successfully" << endl;
}

string DirectSolveEq::Gauss(vector<vector<double> >a, vector<double> b, int n)
{
	string result;
	double mm;
	vector<double> jie(n);
	for (int k = 1; k < n; k++)
	{
		if (a[k - 1][k - 1] == 0)
		{
			result = "fail";
			return result;
		}
		for (int i = k + 1; i < n + 1; i++)
		{
			mm = a[i - 1][k - 1] / a[k - 1][k - 1];
			for (int j = k + 1; j < n + 1; j++)
			{
				a[i - 1][j - 1] = a[i - 1][j - 1] - mm * a[k - 1][j - 1];

			}
			b[i - 1] = b[i - 1] - mm * b[k - 1];
			for (int j = 1; j < k + 1; j++)
				a[i - 1][j - 1] = 0;
		}
		//print((double**)a,b,n);
	}
	if (a[n - 1][n - 1] == 0)
	{
		result = "fail";
		return result;
	}
	result = "Gauss:\n";
	jie[n - 1] = b[n - 1] / a[n - 1][n - 1];
	for (int k = n - 1; k > 0; k--)
	{
		double temp = 0;
		for (int j = k + 1; j < n + 1; j++)
			temp += a[k - 1][j - 1] * jie[j - 1];
		jie[k - 1] = (b[k - 1] - temp) / a[k - 1][k - 1];
	}
	for (int i = 0; i < n - 1; i++)
		result = result + "x" + to_string(i + 1) + " = " + to_string(jie[i]) + "\n";
	result = result + "x" + to_string(n) + " = " + to_string(jie[n - 1]) + "\n";
	return result;
}

string DirectSolveEq::lie_Gauss(vector<vector<double> >a, vector<double> b, int n)
{
	string result;
	for (int k = 1; k < n; k++)
	{
		double max = abs(a[k - 1][k - 1]);
		int lie_hao = k;
		for (int i = k; i < n + 1; i++)
			if (abs(a[i - 1][k - 1]) > max)
			{
				max = abs(a[i - 1][k - 1]);
				lie_hao = i;
			}
		for (int j = k; j < n + 1; j++)
		{
			double temp = a[k - 1][j - 1];
			a[k - 1][j - 1] = a[lie_hao - 1][j - 1];
			a[lie_hao - 1][j - 1] = temp;
		}
		for (int i = k + 1; i < n + 1; i++)
		{
			double mm = a[i - 1][k - 1] / a[k - 1][k - 1];
			for (int j = k + 1; j < n + 1; j++)
			{
				a[i - 1][j - 1] = a[i - 1][j - 1] - mm * a[k - 1][j - 1];

			}
			b[i - 1] = b[i - 1] - mm * b[k - 1];
			for (int j = 1; j < k + 1; j++)
				a[i - 1][j - 1] = 0;
		}
	}
	result = result+ "使用列主元消元法求解结果如下：\n";
	double* jie = new double[n];
	jie[n - 1] = b[n - 1] / a[n - 1][n - 1];
	for (int k = n - 1; k > 0; k--)
	{
		double temp = 0;
		for (int j = k + 1; j < n + 1; j++)
			temp += a[k - 1][j - 1] * jie[j - 1];
		jie[k - 1] = (b[k - 1] - temp) / a[k - 1][k - 1];
	}
	for (int i = 0; i < n - 1; i++)
		result = result + "x" + to_string(i + 1) + " = " + to_string(jie[i]) + "\n";
	result = result + "x" + to_string(n) + " = " + to_string(jie[n - 1]) + "\n";
	return result;
}

string DirectSolveEq ::Chasing_method(vector<vector<double> >a, vector<double>d, int n)
{
	vector<double>x(n);
	vector<double>alpha(n);
	vector<double>gama(n);
	vector<double>beta(n);
	vector<double>y(n);
	alpha[0] = a[0][0];
	beta[0] = a[0][1] / a[0][0]; y[0] = d[0] / a[0][0];
	for (int i = 1; i < n; i++)
	{
		gama[i] = a[i][i - 1];
		alpha[i] = a[i][i] - gama[i] * beta[i - 1];
		if (i < n - 1)
		{
			beta[i] = a[i][i + 1] / alpha[i];
		}
		y[i] = (d[i] - a[i][i - 1] * y[i - 1]) / alpha[i];
	}
	x[n - 1] = y[n - 1];
	for (int i = n - 2; i >= 0; i--)
	{
		x[i] = y[i] - beta[i] * x[i + 1];
	}
	string result = "Chassing:\n";
	for (int i = 1; i <= n; i++)
	{
		result = result + "x" + to_string(i) + " = " + to_string(x[i - 1]) + "\n";
	}
	return result;
}

string DirectSolveEq::Square(vector<vector<double> >a, vector<double>b, int n)
{
	vector<double> tmp(n), x(n), y(n);
	for (int k = 0; k <n; k++)
	{
		double s1 = 0;
		for (int m = 0; m <= k - 1; m++)	s1 += pow(a[k][m], 2);
		a[k][k] = sqrt(a[k][k] - s1);
		for (int i = k + 1; i < n; i++)
		{
			double s2 = 0;
			for(int m=0;m<=k-1;m++)	s2+= a[i][m] * a[k][m];
			a[i][k] = (a[i][k] - s2) / a[k][k];
		}
		double s3 = 0;
		for (int m = 0; m <= k - 1; m++)
			s3 += a[k][m] * y[m];
		y[k] = (b[k] - s3) / a[k][k];
	}
	x[n-1] = y[n-1] / a[n-1][n-1];
	for (int k = n - 2; k >= 0; k--)
	{
		double s4 = 0;
		for (int m = k + 1; m < n; m++)
			s4 += a[m][k] * x[m];
		x[k] = (y[k] - s4) / a[k][k];
	}
	string result = "Sqr :\n";
	for (int i = 0; i < n; i++)
	{
		result = result + "x" + to_string(i + 1) + " = " + to_string(x[i]) + "\n";
	}
	return result;
}