#ifndef ODESOLVER_H
#define ODESOLVER_H

#include "ndarray.h"

namespace OdeSolver {
    typedef ndarray(*func_t)(real_type, const ndarray&);
    typedef struct {
        real_type x;
        ndarray y;
    } point;
    point EulerMethod(func_t func, const point& init, real_type h, real_type x_tar);
    point EulerAdvanced(func_t func, const point& init, real_type h, real_type x_tar);
    point RungeKuttaMethod(func_t func, const point& init, real_type h, real_type x_tar, int order);
    point AdamsMethod(func_t func, const point& init, real_type h, real_type x_tar, int q);

    extern int max_iter;
    extern std::vector<point> path;
};

#endif // ODESOLVER_H