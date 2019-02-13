#include "optargs.h"
#include <string.h>
#include <assert.h>

int optargs_parse(char *const argv[], const int argc, const optargs_callback callback)
{
    int i;
    char *argname;
    const char *argvalue;
    char *sepch = NULL;
    int result;

    assert(callback != NULL);

    for(i = 1; i < argc; i++)
    {
        argname = argv[i];
        if(*argname == '-')
        {
            argname++;
            if(*argname == '-')
                argname++;

            if(*argname == '\0')
            {
                i++;
                break;
            }

            sepch = strchr(argname, '=');
            if(sepch != NULL)
            {
                *sepch = '\0';
                argvalue = *(sepch + 1U) != '\0' ? (sepch + 1U) : NULL;
            }
            else
            {
                argvalue = (i + 1 < argc && *argv[i + 1] != '-') ? argv[i + 1] : NULL;
                if(argvalue != NULL)
                    i++;
            }
        }
        else
        {
            argname = NULL;
            argvalue = argv[i];
        }

        result = callback(argname, argvalue);
        if(result != 0)
            return result;

        if(sepch != NULL)
        {
            *sepch = '=';
            sepch = NULL;
        }
    }

    for(; i < argc; i++)
    {
        result = callback(NULL, argv[i]);
        if(result != 0)
            return result;
    }

    return 0;
}
