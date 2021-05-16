#pragma once
#include <cmath>
#include <vector>
#include <iostream>
#include "TypeTrans.h"

extern int M_error;      //ȫ�ֱ������洢������Ϣ��
#define E_InvalidChar 1 //����Ƿ��ַ�
#define E_Unknown 2  //δ֪����
#define E_TooManyConst 3//������ೣ��
#define E_Turn 4 //���������޷���
#define E_odd 5 //Simpson�����У������������Ϊ����
using namespace std;
class Intergration
{
public:
	Intergration();
	double CTF(double a, double b, int n, double (*fun)(double, char*, double*), char* pos_e, double* val);
	double CSF(double a, double b, int n, double (*fun)(double, char*, double*), char* pos_e, double* val);
	vector<double> VariableStepSize(double a, double b, double e, double (*f)(double,  char*, double*), char* pos_e, double* val);
	vector<double> Romberg(double a, double b, double e, double (*f)(double, char*, double*), char* pos_e, double* val);
private:
};

double f1(double x);
double f2(double x);
double f3(double x);
double f4(double x);

int isp(char c);
int icp(char c);
int mid_to_pos(char* mid_e, char* pos_e);
void parse(char* funct, char* pos_e, double* val);
double evaluate(double arg, char* pos_e, double* val);