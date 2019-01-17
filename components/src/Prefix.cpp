#include "Prefix.hpp"

namespace Prefix
{
    static const std::pair<std::string, int> _prefix_none("", 0);
    static const std::pair<std::string, int> _prefix_min("u", -6);
    static const std::pair<std::string, int> _prefix_max("G", 9);

    static const std::unordered_map<std::string, int> _prefixes
    {
        _prefix_max,
        /*{ "Y", 24 },
        { "Z", 21 },
        { "E", 18 },
        { "P", 15 },
        { "T", 12 },
        { "G", 9 },*/
        { "M", 6 },
        { "k", 3 },
        /*{ "h", 2 },
        { "da", 1 },*/
        _prefix_none,
        /*{ "d", -1 },
        { "c", -2 },*/
        { "m", -3 },
        /*{ "u", -6 },
        { "n", -9 },
        { "p", -12 },
        { "f", -15 },
        { "a", -18 },
        { "z", -21 },
        { "y", -24 }*/
        _prefix_min
    };

    int CalcExponent(const double value)
    {
        if(value == 0.0) return 0;

        int exponent = (int)floor(log10(value));
        return /*abs(exponent) > 3 ? (exponent / 3) * 3 : */exponent;
    }

    bool TryGetSymbol(const int exponent, std::string &result)
    {
        for(std::unordered_map<std::string, int>::const_iterator i = _prefixes.cbegin(); i != _prefixes.cend(); i++)
        {
            if(exponent == i->second)
            {
                result = i->first;
                return true;
            }
        }

        return false;
    }

    std::string GetSymbol(const int exponent)
    {
        if(exponent < _prefix_min.second)
            return _prefix_min.first;
        else if(exponent > _prefix_max.second)
            return _prefix_max.first;

        std::string result;
        if(TryGetSymbol(exponent, result))
            return result;

        return _prefix_none.first;
    }

    bool TryGetMultiplier(const std::string &symbol, double &result)
    {
        return TryGetMultiplier(symbol.c_str(), result);
    }

    bool TryGetMultiplier(const char *const symbol, double &result)
    {
        if(symbol == NULL || *symbol == '\0')
        {
            result = 1.0;
            return true;
        }

        std::unordered_map<std::string, int>::const_iterator entry = _prefixes.find(symbol);
        if(entry != _prefixes.cend())
        {
            result = pow(10.0, entry->second);
            return true;
        }

        return false;
    }

    bool TryGetMultiplier(const std::string &symbol1, const std::string &symbol2, double &result)
    {
        return TryGetMultiplier(symbol1.c_str(), symbol2.c_str(), result);
    }

    bool TryGetMultiplier(const char *const symbol1, const char *const symbol2, double &result)
    {
        double prefix1, prefix2;

        if(!TryGetMultiplier(symbol1, prefix1) || !TryGetMultiplier(symbol2, prefix2))
            return false;

        result = prefix1 / prefix2;
        return true;
    }

    double GetMultiplier(const std::string &symbol)
    {
        return GetMultiplier(symbol.c_str());
    }

    double GetMultiplier(const char *const symbol)
    {
        double result;
        return TryGetMultiplier(symbol, result) ? result : 1.0;
    }

    double GetMultiplier(const std::string &symbol1, const std::string &symbol2)
    {
        return GetMultiplier(symbol1.c_str(), symbol2.c_str());
    }

    double GetMultiplier(const char *const symbol1, const char *const symbol2)
    {
        double result;
        return TryGetMultiplier(symbol1, symbol2, result) ? result : 1.0;
    }

    bool Apply(const std::string &symbol, double &result)
    {
        return Apply(symbol.c_str(), result);
    }

    bool Apply(const char *const symbol, double &result)
    {
        double value;

        if(TryGetMultiplier(symbol, value))
        {
            result *= value;
            return true;
        }

        return false;
    }

    bool Apply(const std::string &symbol1, const std::string &symbol2, double &result)
    {
        return Apply(symbol1.c_str(), symbol2.c_str(), result);
    }

    bool Apply(const char *const symbol1, const char *const symbol2, double &result)
    {
        double value;

        if(TryGetMultiplier(symbol1, symbol2, value))
        {
            result *= value;
            return true;
        }

        return false;
    }
}
