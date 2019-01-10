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

    if(symbol == NULL || *symbol == '\0')
        return &_si_prefix_default;

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
    std::string input;
    bool isParallel;

    std::cout << "Resistors are parallel (y/n)? ";
    std::getline(std::cin, input);
    if(input == "y") isParallel = true;
    else isParallel = false;

    while(true)
    {
        char *prefixPart;
        prefixdata *prefix;

        // Input resistance
        std::cout << "Resistance: ";
        std::getline(std::cin, input);
        if(input.empty()) break;
        double resistance = strtod(input.c_str(), &prefixPart);

        prefix = prefixdata_findbysymbol(prefixPart);
        if(prefix != NULL)
            resistance *= prefix->multiplier;

        // Input tolerance
        std::cout << "Tolerance: ";
        std::getline(std::cin, input);
        if(input.empty()) break;
        double tolerance = strtod(input.c_str(), &prefixPart);

        prefix = prefixdata_findbysymbol(prefixPart);
        if(prefix != NULL)
            tolerance *= prefix->multiplier;

        // Input max. effect
        std::cout << "Max. effect: ";
        std::getline(std::cin, input);
        if(input.empty()) break;
        double maxEffect = strtod(input.c_str(), &prefixPart);

        prefix = prefixdata_findbysymbol(prefixPart);
        if(prefix != NULL)
            maxEffect *= prefix->multiplier;

        // Create a new resistor and put it in the vector
        resistors.push_back(Resistor(resistance, tolerance, maxEffect));
    }

    Resistor result = Resistor::Combine(resistors, isParallel);
    std::cout << "Total resistance: " << result.GetResistance() << std::endl;

    return 0;
}
