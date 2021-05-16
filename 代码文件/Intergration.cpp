#include "Intergration.h"
#include <cmath>
#include <array>
#include <iostream>
#include "TypeTrans.h"

#define maxn 100
#define error 0.00000001
#define SIN(x) (sin(x))
#define COS(x) (cos(x))
#define TAN(x) (tan(x))

int M_error;
using namespace std;

Intergration::Intergration()
{
	cout << "class is been created successfully" << endl;
}

double evaluate(double arg, char* pos_e, double* val)
{
    double _stack[maxn];
    int top;
    double x, y;
    char c;
    top = -1;
    int i = 0;
    c = pos_e[0];
    while (c != '\0')
    {
        if (c == 'x')
        {
            _stack[++top] = arg;
        }
        else if (islower(c))
        {
            _stack[++top] = val[c - 'a'];
        }
        else
        {
            switch (c)
            {
            case '+':
                x = _stack[top--];
                _stack[top] += x;
                break;
            case '-':
                x = _stack[top--];
                _stack[top] -= x;
                break;
            case '*':
                x = _stack[top--];
                _stack[top] *= x;
                break;
            case '/':
                x = _stack[top--];
                if (abs(x) < error)
                {
                    cerr << "Error: divisor is 0." << endl;
                    exit(1);
                }
                _stack[top] /= x;
                break;
            case '^': //y^x
                x = _stack[top--];
                y = _stack[top];
                if (x == 0.5)
                {
                    _stack[top] = sqrt(y);
                    break;
                }

                if (abs(round(x) - x) >= error)
                {
                    cerr << "Error: y^x,x should be an integer or 0.5." << endl;
                    exit(1);
                }

                if ((int)x == 0) _stack[top] = 1;
                else
                {
                    double z;
                    int j, k;
                    if (x > 0) j = (int)x;
                    else j = -1 * (int)x;
                    for (z = 1, k = 1; k <= j; k++)
                    {
                        z *= y;
                    }
                    if (x < 0) z = 1 / z;
                    _stack[top] = z;
                }
                break;
            case 'S':
                x = _stack[top];
                _stack[top] = SIN(x);
                break;
            case 'C':
                x = _stack[top];
                _stack[top] = COS(x);
                break;
            case 'T':
                x = _stack[top];
                _stack[top] = TAN(x);
                break;
            case 'L':
                x = _stack[top];
                _stack[top] = log(x);
                break;
            case 'E':
                x = _stack[top];
                _stack[top] = exp(x);
                break;

            default:
                M_error = E_InvalidChar;
                return 0;
            }
        }
        c = pos_e[++i];
    }
    if (top > 0)
    {
        M_error = E_Unknown;
        return 0;
    }
    return _stack[top];
}

int icp(char c)
{
    if (isupper(c)) return 6;
    switch (c)
    {
    case '^': return 4;
    case '*':
    case '/':
        return 2;
    case '+':
    case '-':
        return 1;
    }
}

int isp(char c)
{
    if (isupper(c)) return 5;
    switch (c)
    {
    case '^':return 3;
    case '*':
    case '/':
        return 2;
    case '+':
    case '-':
        return 1;
    case '(':
        return 0;
    case '&':
        return -1;
    }
}

int mid_to_pos(char* mid_e, char* pos_e)
{
    char _stack[maxn], c;
    int top, i, j;
    _stack[0] = '&';
    top = 0;
    i = 0;
    j = 0;
    c = mid_e[0];
    while (c != '\0') {
        if (islower(c))
        {
            pos_e[j++] = c;
        }
        else if (isupper(c))
        {
            while (icp(c) <= isp(_stack[top]))
                pos_e[j++] = _stack[top--];
            _stack[++top] = c;
        }
        else
        {
            switch (c)
            {
            case '+':
            case '-':
            case '*':
            case '/':
            case '^':
                while (icp(c) <= isp(_stack[top]))
                    pos_e[j++] = _stack[top--];
                _stack[++top] = c;
                break;
            case '(':
                _stack[++top] = c;
                break;
            case ')':
                while (_stack[top] != '(')
                    pos_e[j++] = _stack[top--];
                top--;
                break;
            default:
                return 1;
            }
        }
        c = mid_e[++i];
    }
    while (top > 0)
        pos_e[j++] = _stack[top--];
    pos_e[j] = '\0';
    return 0;
}

void parse(char* funct, char* pos_e, double* val)
{
    char mid_e[maxn];
    int i = 0;
    int val_idx = 0;
    int mid_idx = 0;

    while (funct[i] != '\0')
    {
        cout << "i=" << i << endl;
        cout << "funct[i]=" << funct[i] << endl;
        char c = funct[i];
        if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '(' || c == ')' || c == 'x')
        {
            mid_e[mid_idx++] = c;
            i++;
        }
        else if (c == 's') //sin(x)
        {
            if (funct[i + 1] == '\0' || funct[i + 2] == '\0')
            {
                M_error = E_InvalidChar;
                return;
            }
            if (funct[i + 1] != 'i' || funct[i + 2] != 'n')
            {
                M_error = E_InvalidChar;
                return;
            }
            mid_e[mid_idx++] = 'S';
            i += 3;
        }
        else if (c == 'c') //cos(x)
        {
            if (funct[i + 1] == '\0' || funct[i + 2] == '\0')
            {
                M_error = E_InvalidChar;
                return;
            }
            if (funct[i + 1] != 'o' || funct[i + 2] != 's')
            {
                M_error = E_InvalidChar;
                return;
            }
            mid_e[mid_idx++] = 'C';
            i += 3;
        }
        else if (c == 't') //tan(x)
        {
            if (funct[i + 1] == '\0' || funct[i + 2] == '\0')
            {
                M_error = E_InvalidChar;
                return;
            }
            if (funct[i + 1] != 'a' || funct[i + 2] != 'n')
            {
                M_error = E_InvalidChar;
                return;
            }
            mid_e[mid_idx++] = 'T';
            i += 3;
        }
        else if (c == 'l') //ln(x)
        {
            if (funct[i + 1] == '\0')
            {
                M_error = E_InvalidChar;
                return;
            }
            if (funct[i + 1] != 'n')
            {
                M_error = E_InvalidChar;
                return;
            }
            mid_e[mid_idx++] = 'L';
            i += 2;
        }
        else if (c == 'e') //e^x
        {
            if (funct[i + 1] == '\0')
            {
                M_error = E_InvalidChar;
                return;
            }
            if (funct[i + 1] != '^')
            {
                M_error = E_InvalidChar;
                return;
            }
            mid_e[mid_idx++] = 'E';
            i += 2;
        }
        else if ('0' <= c && c <= '9')
        {
            if ((char)(val_idx + 'a') == 'x') val_idx++;
            if (val_idx >= 26)
            {
                M_error = E_TooManyConst;
                return;
            }

            double temp = 0;
            while (funct[i] != '\0' && '0' <= funct[i] && funct[i] <= '9')
            {
                temp = temp * 10 + funct[i] - '0';
                i++;
            }


            if (funct[i] != '\0' && funct[i] == '.')
            {
                i++;
                int wei = 0;
                if ('0' > funct[i] || funct[i] > '9')
                {
                    M_error = E_InvalidChar;
                    return;
                }
                while (funct[i] != '\0' && '0' <= funct[i] && funct[i] <= '9')
                {
                    temp = temp * 10 + funct[i] - '0';
                    wei++;
                    i++;
                }
                while (wei > 0)
                {
                    temp /= 10;
                    wei--;
                }
            }
            cout << "i=" << i << endl;
            cout << "val_idx=" << val_idx << endl;
            mid_e[mid_idx++] = 'a' + val_idx;
            cout << "mid_idx=" << mid_idx << endl;
            val[val_idx] = temp;

            val_idx++;
        }
        else
        {
            M_error = E_InvalidChar;
            return;
        }
    }
    cout << "end parse" << endl;
    cout << "mid_idx=" << mid_idx;
    mid_e[mid_idx] = '\0';
    cout << "mid_e=" << mid_e << endl;
    cout << "val=";
    for (int idx = 0; idx < val_idx; idx++)
    {
        cout << val[idx] << " ";
    }
    cout << endl;

    int rt = mid_to_pos(mid_e, pos_e);
    cout << "pos_e=" << pos_e << endl;
    if (rt == 1)
    {
        M_error = E_Unknown;
        return;
    }
}



double f1(double x)
{
	return sqrt(4 - sin(x) * sin(x));
}

double   f2(double x)
{
    if (x == 0)
        return 1;
    return sin(x) / x;
}

double f3(double x)
{
    return exp(x) / (4 + x * x);
}

double f4(double x)
{
    return log(1 + x) / (1 + x * x);
}

double Intergration::CTF(double a, double b, int n, double (*fun)(double,char*,double*), char* pos_e, double* val)
{
	double h = (b - a) / n;
	double ans = 0;
	for (int i = 1; i <= n - 1; i++)
	{
		double x = a + i * h;
		ans = ans + fun(x,  pos_e,  val);
	}
	ans = ans * 2;
	ans = ans + fun(a, pos_e, val) + fun(b, pos_e, val);
	ans = ans * h / 2;
	return ans;
}

double Intergration::CSF(double a, double b, int n, double (*fun)(double,  char*, double*), char* pos_e, double* val)
{
	int m = n / 2;
	double h = (b - a) / n;
	double ans = 0;
	for (int i = 1; i <= m - 1; i++)
	{
		double x = a + 2 * i * h;
		ans = ans + fun(x, pos_e, val);
	}
	ans = ans * 2;
	double temp = 0;
	for (int i = 1; i <= m; i++)
	{
		double x = a + (2 * i - 1) * h;
		temp = temp + fun(x, pos_e, val);
	}
	temp = temp * 4;
	ans = ans + temp;
	ans = (ans + fun(a, pos_e, val) + fun(b, pos_e, val)) * h / 3;
	return ans;
}

vector<double> Intergration::VariableStepSize(double a, double b, double e, double (*f)(double, char*, double*), char* pos_e, double* val)
{//f为求积函数,a和b为求积区间,e是精确要求
	long long i, times = 1;//用来记录增加节点的个数
	double ans, t, sum;
	ans = (f(a, pos_e, val) + f(b, pos_e, val)) * (b - a) / 2;//利用梯形公式粗略计算积分
	double numerator, denominator = 1;
	do//至少循环一次
	{
		t = ans;
		//        printf("t=%.7lf\n",t);
		sum = 0;
		numerator = 1;    denominator *= 2;
		for (i = 0; i < times; i++)
		{//新增加的点用了两次
			sum = sum + 2 * f(numerator / denominator, pos_e, val);
			numerator += 2;
		}//End for-i
		times *= 2;
		sum = (sum) / ((b - a) * times * 2);//新增加的部分
		ans = t / 2 + sum;
	} while ((ans - t - e) >= 0);//满足精度要求以后退出
	vector<double> result;
	result.push_back(ans);
	result.push_back((b - a) / times);
	return result;
}

vector<double> Intergration::Romberg(double a, double b, double e, double (*f)(double, char*, double*),char* pos_e, double* val)
{//f为求积函数,a和b为求积区间,e是精确要求
	int i, j, k = 1;//每次递推都可以推导一行 
	int times = 1;
	double sum;
	double table[10][10] = { 0 };//递推的二维矩阵,简单地固定位10*10
	double coef[10][2] = { 0 };//用来保存系数,比如说4/3,16/15
	double LastLeft, LastRight;//记录推导一行中最后两个数，用以判断精度
	double numerator, denominator = 1;//分子分母
	table[0][0] = (f(a, pos_e, val) + f(b,pos_e, val) * (b - a)) / 2;    numerator = 4;
	for (i = 1; i < 10; i++)
	{
		coef[i][0] = numerator / (numerator - 1);//前一个系数，比如说4/3
		coef[i][1] = (-1) / (numerator - 1);//后一个系数,比如说-1/3
		numerator *= 4;
	}//End for-i
	do
	{
		sum = 0;
		numerator = 1;
		denominator *= 2;
		for (i = 0; i < times; i++)
		{
			sum = sum + f(numerator / denominator, pos_e, val);
			numerator += 2;
		}
		times *= 2;   sum = (sum) / ((b - a) * times * 2);
		table[k][0] = table[k - 1][0] / 2 + sum;//求得Tn

		for (i = 1; i <= k; i++)//向外递推过程
			table[k][i] = coef[i][0] * table[k][i - 1] + coef[i][1] * table[k - 1][i - 1];
		LastLeft = table[k][k - 1]; LastRight = table[k][k];
		k++;
	} while ((LastRight - LastLeft - e) >= 0);//满足精度则退出
	vector<double> result;
	result.push_back(LastRight);
	result.push_back((b - a) / times);
	return result;
}

