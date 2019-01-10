#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include "Resistor.hpp"

#define arraycount(arr) (sizeof(arr) / sizeof(*arr))

typedef struct _prefixdata
{
    char name[33];
    char symbol[3];
    double multiplier;
} prefixdata;

prefixdata _si_prefix_default = { "", "", 1.0 };
prefixdata _si_prefixes[] =
{
    { "Giga", "G", 1000000000.0 },
    { "Mega", "M", 1000000.0 },
    { "kilo", "k", 1000.0 },
    { "hecto", "h", 100.0 },
    { "deca", "da", 10.0 },

    { "deci", "d", 0.1 },
    { "centi", "c", 0.01 },
    { "milli", "m", 0.001 },
    { "micro", "u", 0.000001 },
    { "nano", "n", 0.000000001 }
};

prefixdata *prefixdata_findbysymbol(const char *const symbol)
{
    size_t i;

    if(*symbol == '\0')
    {
        return &_si_prefix_default;
    }

    for(i = 0U; i < arraycount(_si_prefixes); i++)
    {
        if(strcmp(symbol, _si_prefixes[i].symbol) == 0)
        {
            return &_si_prefixes[i];
        }
    }

    return NULL;
}

int main()
{
    std::vector<Resistor> resistors;

    return 0;
}
