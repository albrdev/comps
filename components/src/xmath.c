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
