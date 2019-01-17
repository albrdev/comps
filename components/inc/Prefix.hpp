#ifndef _PREFIX_HPP_
#define _PREFIX_HPP_

#include <map>
#include <unordered_map>
#include <cmath>

namespace Prefix
{
    int CalcExponent(const double value);
    bool TryGetSymbol(const int exponent, std::string &result);
    std::string GetSymbol(const int exponent);

    bool TryGetMultiplier(const std::string &symbol, double &result);
    bool TryGetMultiplier(const char *const symbol, double &result);
    bool TryGetMultiplier(const std::string &symbol1, const std::string &symbol2, double &result);
    bool TryGetMultiplier(const char *const symbol1, const char *const symbol2, double &result);

    double GetMultiplier(const std::string &symbol);
    double GetMultiplier(const char *const symbol);
    double GetMultiplier(const std::string &symbol1, const std::string &symbol2);
    double GetMultiplier(const char *const symbol1, const char *const symbol2);

    bool Apply(const std::string &symbol, double &result);
    bool Apply(const char *const symbol, double &result);
    bool Apply(const std::string &symbol1, const std::string &symbol2, double &result);
    bool Apply(const char *const symbol1, const char *const symbol2, double &result);
}

#endif // _PREFIX_HPP_
