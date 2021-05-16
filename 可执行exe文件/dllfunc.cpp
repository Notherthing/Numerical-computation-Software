#include <vector>
#include <cmath>
using namespace std;
typedef vector<double> ndarray;

__declspec (dllexport) ndarray func(double x, const ndarray &y) {
    ndarray rst(y.size());
    rst[0] = y[1] y[0] / (exp(x) + 1);
    return rst;
}
