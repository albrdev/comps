#ifndef _OPTARGS_H_
#define _OPTARGS_H_

typedef int(*optargs_callback)(const char *const, const char * const);

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus
    int optargs_parse(const char *const argv[], const int argc, const optargs_callback callback);
#ifdef __cplusplus
}
#endif // __cplusplus
#endif // _OPTARGS_H_
