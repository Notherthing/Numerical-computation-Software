#ifndef NDARRAY_H
#define NDARRAY_H

#include <vector>

//#include <iostream>
//using namespace std;
//#define mydebug(x) cout << __FUNCTION__ << (": " #x "\n") << (x) << endl;


typedef double real_type;
typedef std::vector<real_type> ndarray;

ndarray operator+(const ndarray& a1, const ndarray& a2);
ndarray operator-(const ndarray& a1, const ndarray& a2);
ndarray operator*(real_type number, const ndarray& a);

#endif // NDARRAY_H