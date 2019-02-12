#include "xmath.h"
#include <math.h>

double floorn(const double value, const int prec)
{
    double multiplier = pow(10, prec);
    return floor(value * multiplier) / multiplier;
}

double ceiln(const double value, const int prec)
{
    double multiplier = pow(10, prec);
    return ceil(value * multiplier) / multiplier;
}

double roundn(const double value, const int prec)
{
    double multiplier = pow(10, prec);
    return round(value * multiplier) / multiplier;
}

int getdigit(const double value, const unsigned int index)
{
    return (int)(value * pow(10, index)) % 10;
}

int mod_trunc(const int a, const int n)
{
    return a - (n * (int)((double)a / (double)n));
}

int mod_floor(const int a, const int n)
{
    return a - (n * (int)floor((double)a / (double)n));
}

int mod_euclidean(const int a, const int n)
{
    return (int)(sgn(n) * floor((double)a / (double)n));
}
