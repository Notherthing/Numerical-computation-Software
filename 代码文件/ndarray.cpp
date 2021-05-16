#include "ndarray.h"
#include <cassert>

#define repo(i, l, r) for (int i = l, i##end = r; i < i##end; ++i)

ndarray operator+(const ndarray& a1, const ndarray& a2)
{
    assert(a1.size() == a2.size());
    ndarray rst(a1);
    repo(i, 0, a1.size())
        rst[i] += a2[i];
    return rst;
}

ndarray operator-(const ndarray& a1, const ndarray& a2)
{
    assert(a1.size() == a2.size());
    ndarray rst(a1);
    repo(i, 0, a1.size())
        rst[i] -= a2[i];
    return rst;
}

ndarray operator*(real_type number, const ndarray& a)
{
    ndarray rst(a);
    repo(i, 0, a.size())
        rst[i] *= number;
    return rst;
}