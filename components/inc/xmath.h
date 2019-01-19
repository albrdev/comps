#ifndef _XMATH_H_
#define _XMATH_H_

#ifdef __cplusplus
extern "C"
{
#endif
    double floorn(const double value, const int prec);
    double ceiln(const double value, const int prec);
    double roundn(const double value, const int prec);

    int getdigit(const double value, const unsigned int index);
#ifdef __cplusplus
} // extern "C"
#endif

#endif // _XMATH_H_
