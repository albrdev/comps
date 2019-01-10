#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <map>
#include "Resistor.hpp"

#define arraycount(arr) (sizeof(arr) / sizeof(*arr))

class PrefixData
{
private:
    std::string m_Name;
    std::string m_Symbol;

    double m_Multiplier;

public:
    std::string GetName(void) const { return m_Name; }
    std::string GetSymbol(void) const { return m_Symbol; }
    double GetMultiplier(void) const { return m_Multiplier; }

    PrefixData(const std::string &name, const std::string &symbol, const double multiplier) : PrefixData(symbol, multiplier)
    {
        m_Name = name;
    }

    PrefixData(const std::string &symbol, const double multiplier)
    {
        m_Symbol = symbol;
        m_Multiplier = multiplier;
    }
};

std::map<std::string, double> prefixes
{
    { "G", 1000000000.0 },
    { "M", 1000000.0 },
    { "k", 1000.0 },
    { "h", 100.0 },
    { "da", 10.0 },

    { "d", 0.1 },
    { "c", 0.01 },
    { "m", 0.001 },
    { "u", 0.000001 },
    { "n", 0.000000001 }
};

bool getPrefix(const char *const symbol, double &result)
{
    if(symbol == NULL || *symbol == '\0')
    {
        result = 1.0;
        return true;
    }

    std::map<std::string, double>::const_iterator entry = prefixes.find(symbol);
    if(entry != prefixes.end())
    {
        result = entry->second;
        return true;
    }

    return false;
}

bool getPrefix(const char *const symbol1, const char *const symbol2, double &result)
{
    double prefix1, prefix2;

    if(!getPrefix(symbol1, prefix1) || !getPrefix(symbol2, prefix2))
        return false;

    result = prefix1 / prefix2;
    return true;
}

bool applyPrefix(const char *const symbol, double &result)
{
    double value;

    if(getPrefix(symbol, value))
    {
        result *= value;
        return true;
    }

    return false;
}

bool applyPrefix(const char *const symbol1, const char *const symbol2, double &result)
{
    double value;

    if(getPrefix(symbol1, symbol2, value))
    {
        result *= value;
        return true;
    }

    return false;
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

        // Input resistance
        std::cout << "Resistance: ";
        std::getline(std::cin, input);
        if(input.empty()) break;
        double resistance = strtod(input.c_str(), &prefixPart);
        applyPrefix(prefixPart, resistance);

        // Input tolerance
        std::cout << "Tolerance: ";
        std::getline(std::cin, input);
        if(input.empty()) break;
        double tolerance = strtod(input.c_str(), &prefixPart);
        if(strcmp(prefixPart, "%") == 0)
        {
            tolerance /= 100.0;
        }

        // Input max. effect
        std::cout << "Max. effect: ";
        std::getline(std::cin, input);
        if(input.empty()) break;
        double maxEffect = strtod(input.c_str(), &prefixPart);
        applyPrefix(prefixPart, maxEffect);

        // Create a new resistor and put it in the vector
        resistors.push_back(Resistor(resistance, tolerance, maxEffect));
    }

    Resistor result = Resistor::Combine(resistors, isParallel);
    std::cout << "Total resistance: " << result.GetResistance() << std::endl;
    std::cout << "Tolerance: " << result.GetTolerance() << std::endl;
    std::cout << "Min. resistance: " << result.MinResistance() << std::endl;
    std::cout << "Max. resistance: " << result.MaxResistance() << std::endl;

    return 0;
}
