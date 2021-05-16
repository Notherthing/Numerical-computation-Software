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

TypeTrans::TypeTrans()
{
}

vector<double> TypeTrans::str2vec(string a)
{
    vector<double> result;
    stringstream ss;
    ss << a;
    double temp;
    while (ss >> temp)
    {
        result.push_back(temp);
    }
    ss.clear();
    return result;
}

double  TypeTrans::str2doub(string str)
{
    stringstream ss;
    ss << str;
    double ans;
    ss >> ans;
    ss.clear();
    return ans;
}

int TypeTrans::str2int(string str)
{
    stringstream ss;
    ss << str;
    int ans;
    ss >> ans;
    ss.clear();
    return ans;
}

double TypeTrans::findMax(vector<double> vec) {
    double max = -999999;
    for (auto v : vec) {
        if (max < v) max = v;
    }
    return max;
}

double TypeTrans::findMin(vector<double> vec)
{
    double min = 999999;
    for (auto v : vec) {
        if (min > v) min = v;
    }
    return min;
}

vector<double> TypeTrans::vec(string str)
{
    vector<double> result;
    stringstream ss;
    ss << str;
    string temp;
    double tmp;
    while (ss>>temp)
    {
        tmp = str2doub(temp);
        result.push_back(tmp);
    }
    return result;
}

vector<vector<double> > TypeTrans::nnArray(string str)
{
    string temp;
    vector<vector<double> > result;
    stringstream ss;
    ss << str;
    while (getline(ss,temp))
    {
        result.push_back(vec(temp));
    }
    return result;
}

vector<vector<double>>  TypeTrans::transpose(vector<double> nvec)
{
    int s = nvec.size();
    vector<vector<double> > nnvec(s, vector<double>(2));
    for (int i = 0; i < s; i++)
    {
        nnvec[i][0] = nvec[i];
        nnvec[i][1] = nnvec[i][0];
    }
    return nnvec;
}

bool TypeTrans::fineMar(vector<vector<double> >a, vector<double> b,int n)
{
    int asize = a.size();
    int asizetemp;
    for (int i = 0; i < a.size(); i++)
    {
        if (a[i].size() != asize)     return false;
    }
    if (asize != b.size() || asize != n)    return false;
    if (b.size() != n) return false;
    return true;
}