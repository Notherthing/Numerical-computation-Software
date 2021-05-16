#include <vector>
#include <iostream>
#include <string>
#include "InterpolationCalculation.h"
#include "TypeTrans.h"
using namespace std;

InterpolationCalculation::InterpolationCalculation()
{
	cout << "class is been created successfully" << endl;
}

vector<double> InterpolationCalculation::poly_add(vector<double> a, vector<double> b)
{
	//两个多项式系数相加，0-n分别存x^0 - x^n的系数
	//a.size()必须等于b.size()
	int n = a.size();
	vector<double> ans(n, 0);
	for (int i = 0; i < n; i++)
	{
		ans[i]= a[i] + b[i];
	}
	return ans;
}

vector<double> InterpolationCalculation::lagrange_poly(vector<double> x, vector<double> y)
{
	//x中存提供的x值，y中同下标位置存储对应y的值
	int n = x.size();
	//n表示提供的点的个数
	vector<double> poly(n,0);
	for (int i = 0; i < n; i++)
	{
		vector<double> temp1(n, 0), temp2(n, 0), temp(n, y[i]); int q = 1;
		for (int j = 0; j < n; j++)
		{
			if (j != i)
			{
				for (int k = 0; k < q; k++)
				{
					temp2[k + 1] = temp[k] / (x[i] - x[j]);
					temp1[k] = temp[k] * (-x[j]) / (x[i] - x[j]);
				}
				temp[0] = temp1[0];
				for (int k = 1; k < q; k++)
				{
					temp[k] = temp1[k] + temp2[k];
				}
				temp[q] = temp2[q];
				q++;
			}
		}
		poly = poly_add(poly, temp);
	}
	return poly;  
}

string InterpolationCalculation::lagrange_str(vector<double> coefficient)
{
	string ans = "L(x)=";
	int n = coefficient.size();
	for (int i = 0; i < n; i++)
	{
		if (coefficient[i] == 0) continue;
		else
		{
			if (coefficient[i] > 0 && i!=0)
			{
				ans += "+";
			}
			ans += to_string(coefficient[i]);
			ans += "x^";
			ans += to_string(i);
		}
	}
	return ans;
}

double InterpolationCalculation::value_ans(double x, vector<double>coefficient)
{
	double xn = 1, ans = 0;
	int n = coefficient.size();
	for (int i = 0; i < n; i++)
	{
		ans += xn * coefficient[i];
		xn *= x;
	}
	return ans;
}

double  InterpolationCalculation::newton(double p, vector<double> x, vector<double> y)
{
	int n = x.size()-1;
	vector<vector<double> > table(n + 1);
	for (int i = 0; i <= n; i++) {
		table[i].resize(n + 1);
	}
	for (int i = 0; i <= n; i++) table[0][i] = y[i];
	for (int i = 1; i <= n; i++) {
		for (int j = i; j <= n; j++) {
			table[i][j] = (table[i - 1][j] - table[i - 1][j - 1]) / (x[j] - x[j - i]);
		}
	}
	double res = 0;
	for (int i = 0; i <= n; i++) {
		double temp = table[i][i];
		for (int j = 0; j < i; j++) {
			temp *= p - x[j];
		}
		res += temp;
	}
	return res;
}

string InterpolationCalculation::piecewise(int degree, double p, vector<double> x, vector<double> y)
{
	const string fail = "Piecewise interpolate has failed.";
	int n = x.size();
	vector<double> poly(n,0);
	int i = 0;
	bool flag = false;
	while (i < n)
	{
		if (x[i] <= p && n - i >= degree && x[i + 1] >= p)
		{
			flag = true;
			vector<double> tempx, tempy;
			for (int j = 0; j < degree; j++)
			{
				tempx.push_back(x[i]);
				tempy.push_back(y[i]);
				i++;
			}
			poly = lagrange_poly(tempx, tempy);
			break;
		}
		i++;
	}
	if (!flag)	return fail;
	else
	{
		double result = value_ans(p, poly);
		string result_str = to_string(result);
		return result_str;
	}
}

string InterpolationCalculation::piecewise_poly(int degree, double p, vector<double> x, vector<double> y)
{
	const string fail = "Piecewise interpolate has failed.";
	int n = x.size();
	vector<double> poly(n, 0);
	int i = 0;
	bool flag = false;
	while (i < n)
	{
		if (x[i] <= p && n - i >= degree && x[i + 1] >= p)
		{
			flag = true;
			vector<double> tempx, tempy;
			for (int j = 0; j < degree; j++)
			{
				tempx.push_back(x[i]);
				tempy.push_back(y[i]);
				i++;
			}
			poly = lagrange_poly(tempx, tempy);
			break;
		}
		i++;
	}
	if (!flag)	return fail;
	else
	{
		string result_str = lagrange_str(poly);
		return result_str;
	}
}