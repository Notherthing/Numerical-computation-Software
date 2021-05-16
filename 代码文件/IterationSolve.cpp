#include "IterationSolve.h"
#include<iostream>
#include<math.h>
#include<iomanip>
#include<string>
#include<vector>
using namespace std;
IterationSolve::IterationSolve()
{
	cout << "class is been created successfully" << endl;
}

string IterationSolve::Jacobi(vector<vector<double> >a, vector<double> b, double e)
{
    string result = "Jacobi result here:\n";
    int n = b.size(), j, i, k = 1;
    cout << n << endl;
    double z = 0, m = 0;
    vector<double> x(n, 0), y(n);
    while (1)
    {
        for (i = 0; i < n; i++)
        {
            //cout<<"ok"<<endl;
            for (j = 0; j < n; j++)
            {

                m = m + a[i][j] * x[j];
            }
            m = m - x[i] * a[i][i];
            y[i] = (b[i] - m) / a[i][i];
            if (a[i][i] == 0) printf("!");
            m = 0;
        }
        i = 0;
        while (i < n)
        {
            z = abs(x[i] - y[i]);
            if (z > e)
                break;
            i++;
        }
        if (i != n)
        {
            for (i = 0; i < n; i++)
                x[i] = y[i];
            k++;
        }
        else if (i == n)
            break;
    }
    for (int i = 0; i < n - 1; i++)
        result = result + "x" + to_string(i + 1) + " = " + to_string(y[i]) + "\n";
    result = result + "x" + to_string(n) + " = " + to_string(y[n - 1]) + "\n";
    result = result + "iteration ordinal number is :" + to_string(k) + "\n";
    return result;
}

string IterationSolve::GS(vector<vector<double>> a, vector<double> b, double e)
{
    string result = "Gauss-Seidol result here:\n";
    int n = b.size(), i, j, k;
    double tmp1, tmp2; vector<double> x2(n), x(n);
    for (k = 0; k < 1000; k++)
    {
        for (i = 0; i < n; i++)
            x2[i] = x[i];

        for (i = 0; i < n; i++)
        {
            tmp1 = 0.0;
            tmp2 = 0.0;
            for (j = 0; j < i; j++)
                tmp1 += a[i][j] * x[j];
            for (j = i + 1; j < n; j++)
                tmp2 += a[i][j] * x2[j];
            x[i] = (b[i] - tmp1 - tmp2) / a[i][i];
        }
        for (i = 0, j = 0; i < n; i++)
            if (fabs(x2[i] - x[i]) < e)	j++;
        if (j == n)
        {
            printf("\nThis Gauss-Seidel iterative scheme is convergent!");
            printf("\nNumber of iterations:%d\n", k + 1);
            break;
        }
    }
    for (int i = 0; i < n - 1; i++)
        result = result + "x" + to_string(i + 1) + " = " + to_string(x[i]) + "\n";
    result = result + "x" + to_string(n) + " = " + to_string(x[n - 1]) + "\n";
    result = result + "iteration ordinal number is :" + to_string(j) + "\n";
    return result;
}

string IterationSolve::SOR(vector<vector<double> >a, vector<double> b, double e, double w)
{
    string result = "SOR result here:\n";
    int n = b.size();
    vector<double> x(n);
    vector<double> dx(n);
    vector<double> y(n);//存储X(k)
    double temp = 0;
    double t;//在求向量的范数时存储最大的x
    int i, j;
    int tap = 0;//迭代次数
    for (i = 0; i < n; i++)
    {
        x[i] = dx[i] = 0;
    }
    do//迭代次数的循环
    {
        t = 0;
        for (i = 0; i < n; i++)//存储X(k)
        {
            y[i] = x[i];
        }
        for (i = 0; i < n; i++)
        {
            for (j = 0; j < n; j++)
            {
                if (j < i - 1)
                {
                    temp -= a[i][j] * x[j];//k?
                }
                else
                {
                    temp -= a[i][j] * x[j];
                }
            }
            temp += b[i];
            dx[i] = w / a[i][i] * temp;
            temp = 0;
            x[i] += dx[i];
        }
        for (i = 0; i < n; i++)
        {
            y[i] -= x[i];
            if (fabs(y[i]) > t)
                t = fabs(y[i]);
        }
        tap++;
    } while (t > e);
    for (int i = 0; i < n - 1; i++)
        result = result + "x" + to_string(i + 1) + " = " + to_string(x[i]) + "\n";
    result = result + "x" + to_string(n) + " = " + to_string(x[n - 1]) + "\n";
    result = result + "iteration ordinal number is :" + to_string(tap) + "\n";
    return result;
}