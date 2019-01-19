#ifndef _NUMBERSERIES_HPP_
#define _NUMBERSERIES_HPP_

#include <string>
#include <vector>
#include <set>
#include <cfloat>
#include <cmath>
#include "xmath.h"

class NumberSeries
{
private:
    struct NumberSeriesCompare
    {
        using is_transparent = void;

        bool operator()(const NumberSeries &lhs, const NumberSeries &rhs) const { return lhs.GetName() < rhs.GetName(); }
        bool operator()(const std::string &lhs, const NumberSeries &rhs) const { return lhs < rhs.GetName(); }
        bool operator()(const NumberSeries &lhs, const std::string &rhs) const { return lhs.GetName() < rhs; }
        bool operator()(const std::string &lhs, const std::string &rhs) const { return lhs < rhs; }
    };

    static const std::set<NumberSeries, NumberSeriesCompare> k_StandardSeries;

    std::string m_Name;
    double m_Tolerance;
    std::vector<double> m_Values;

public:
    static double Standardize(const double res)
    {
        int lg = (int)floor(log10(res));
        return res / pow(10, lg);
    }

    static const NumberSeries *Find(const std::string name)
    {
        std::set<NumberSeries, NumberSeriesCompare>::const_iterator result = NumberSeries::k_StandardSeries.find(name);
        return result != k_StandardSeries.cend() ? &(*result) : nullptr;
    }

    std::string GetName(void) const { return m_Name; }
    double GetTolerance(void) const { return m_Tolerance; }

    double GetBaseResistance(double value) const
    {
        value = NumberSeries::Standardize(value);

        if(value < m_Values.front())
            return m_Values.front();
        else if(value > m_Values.back())
            return m_Values.back();

        for(size_t i = 0U; i < m_Values.size(); i++)
        {
            if(m_Values[i] >= value - DBL_EPSILON)
            {
                return m_Values[i];
            }
        }

        return 1.0;
    }

    NumberSeries(const std::string &name, const double tolerance, const std::vector<double> &values)
    {
        m_Name = name;
        m_Tolerance = tolerance;
        m_Values = values;
    }
};

#endif // _NUMBERSERIES_HPP_
