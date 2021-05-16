#include "odesolver.h"
#include <cassert>

#define repo(i, l, r) for (int i = l, i##end = r; i < i##end; ++i)

std::vector<OdeSolver::point> OdeSolver::path;
int OdeSolver::max_iter = 1e7;

static inline ndarray EulerIter(OdeSolver::func_t func, real_type x, const ndarray& y, real_type h) {
    return y + h * func(x, y);
}

OdeSolver::point OdeSolver::EulerMethod(OdeSolver::func_t func, const point& init, real_type h, real_type x_tar)
{
    assert(h > 0);
    ndarray y(init.y);
    path.clear();
    path.push_back(init);
    real_type x = init.x;
    bool reversed = x > x_tar;
    repo(epoch, 0, max_iter) {
        if (!reversed && x >= x_tar) break;
        if (reversed && x <= x_tar) break;
        y = EulerIter(func, x, y, h);
        x += h;
        path.push_back({ x, y });
    }
    return { x, y };
}

static inline ndarray EulerAdIter(OdeSolver::func_t func, real_type x, const ndarray& y, real_type h) {
    ndarray t = y + h * func(x, y);
    return y + h / 2 * (func(x, y) + func(x + h, t));
}

OdeSolver::point OdeSolver::EulerAdvanced(OdeSolver::func_t func, const OdeSolver::point& init, real_type h, real_type x_tar)
{
    assert(h > 0);
    ndarray y(init.y);
    path.clear();
    path.push_back(init);
    real_type x = init.x;
    bool reversed = x > x_tar;
    repo(epoch, 0, max_iter) {
        if (!reversed && x >= x_tar) break;
        if (reversed && x <= x_tar) break;
        y = EulerAdIter(func, x, y, h);
        x += h;
        path.push_back({ x, y });
    }
    return { x, y };
}

static inline ndarray RK2Iter(OdeSolver::func_t func, real_type x, const ndarray& y, real_type h) {
    ndarray k1 = func(x, y);
    ndarray k2 = func(x + h / 2, y + h / 2 * k1);
    return y + h * k2;
}
static inline ndarray RK3Iter(OdeSolver::func_t func, real_type x, const ndarray& y, real_type h) {
    ndarray k1 = func(x, y);
    ndarray k2 = func(x + h / 2, y + h / 2 * k1);
    ndarray k3 = func(x + h, y - h * k1 + 2 * h * k2);
    return y + h / 6 * (k1 + 4 * k2 + k3);
}
static inline ndarray RK4Iter(OdeSolver::func_t func, real_type x, const ndarray& y, real_type h) {
    ndarray k1 = func(x, y);
    ndarray k2 = func(x + h / 2, y + h / 2 * k1);
    ndarray k3 = func(x + h / 2, y + h / 2 * k2);
    ndarray k4 = func(x + h, y + h * k3);
    return y + h / 6 * (k1 + 2 * k2 + 2 * k3 + k4);
}

OdeSolver::point OdeSolver::RungeKuttaMethod(OdeSolver::func_t func, const OdeSolver::point& init, real_type h, real_type x_tar, int order)
{
    assert(h > 0);
    assert(order >= 2 && order <= 4);
    ndarray y(init.y);
    path.clear();
    path.push_back(init);
    real_type x = init.x;

    // unified interface of iter functions
    auto func_iter = RK2Iter;
    if (order == 3) func_iter = RK3Iter;
    else if (order == 4) func_iter = RK4Iter;

    bool reversed = x > x_tar;
    repo(epoch, 0, max_iter) {
        if (!reversed && x >= x_tar) break;
        if (reversed && x <= x_tar) break;
        y = func_iter(func, x, y, h);
        x += h;
        path.push_back({ x, y });
    }
    return { x, y };
}

static inline ndarray Adams2Iter(OdeSolver::func_t func, real_type x, const std::vector<ndarray>& vy, real_type h) {
    return vy[0] + h / 2 * (3 * func(x, vy[0]) - func(x - h, vy[1]));
}
static inline ndarray Adams3Iter(OdeSolver::func_t func, real_type x, const std::vector<ndarray>& vy, real_type h) {
    return vy[0] + h / 12 * (23 * func(x, vy[0]) - 16 * func(x - h, vy[1])
        + 5 * func(x - 2 * h, vy[2]));
}
static inline ndarray Adams4Iter(OdeSolver::func_t func, real_type x, const std::vector<ndarray>& vy, real_type h) {
    return vy[0] + h / 24 * (55 * func(x, vy[0]) - 59 * func(x - h, vy[1])
        + 37 * func(x - 2 * h, vy[2]) - 9 * func(x - 3 * h, vy[3]));
}
static inline std::vector<ndarray> getPrev(const ndarray y[], int idx, int q, const int maxq) {
    switch (q) {
    case 2:
        return { y[idx], y[(idx - 1 + maxq) % maxq] };
    case 3:
        return { y[idx], y[(idx - 1 + maxq) % maxq], y[(idx - 2 + maxq) % maxq] };
    case 4:
        return { y[idx], y[(idx - 1 + maxq) % maxq], y[(idx - 2 + maxq) % maxq], y[(idx - 3 + maxq) % maxq] };
    default:
        assert(0);
        return std::vector<ndarray>();
    }
}

OdeSolver::point OdeSolver::AdamsMethod(OdeSolver::func_t func, const OdeSolver::point& init, real_type h, real_type x_tar, int q)
{
    assert(h > 0);
    assert(q >= 2 && q <= 4);
    static const int maxq = 4;
    ndarray y[maxq]{ init.y };
    real_type x = init.x;
    for (int i = 1; i < q; ++i)
        y[i] = RK4Iter(func, x + (i - 1) * h, y[i - 1], h);
    path.clear();
    for (int i = 0; i < q; ++i)
        path.push_back({ x + i * h, y[i] });

    // unified interface of iter functions
    auto func_iter = Adams2Iter;
    if (q == 3) func_iter = Adams3Iter;
    else if (q == 4) func_iter = Adams4Iter;

    x += (q - 1) * h;
    int idx = q - 1;
    bool reversed = x > x_tar;
    repo(epoch, 0, max_iter) {
        if (!reversed && x >= x_tar) break;
        if (reversed && x <= x_tar) break;
        y[(idx + 1) % maxq] = func_iter(func, x, getPrev(y, idx, q, maxq), h);
        x += h;
        idx = (idx + 1) % maxq;
        path.push_back({ x, y[idx] });
    }
    return { x, y[idx] };
}