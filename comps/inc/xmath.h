#ifndef _XMATH_H_
#define _XMATH_H_

#define sgn(x) (((x) > 0) - ((x) < 0))

#define dectopc(x) ((x) * 100.0)
#define pctodec(x) ((x) / 100.0)

#define dectopm(x) ((x) * 1000.0)
#define pmtodec(x) ((x) / 1000.0)

#define dectoppm(x) ((x) * 1000000.0)
#define ppmtodec(x) ((x) / 1000000.0)

#ifdef __cplusplus
extern "C"
{
#endif
    double floorn(const double value, const int prec);
    double ceiln(const double value, const int prec);
    double roundn(const double value, const int prec);

    int getdigit(const double value, const unsigned int index);

    int mod_trunc(const int a, const int n);
    int mod_floor(const int a, const int n);
    int mod_euclidean(const int a, const int n);
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _XMATH_H_
