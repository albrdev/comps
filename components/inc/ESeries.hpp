#ifndef _ESERIES_HPP_
#define _ESERIES_HPP_

#include <string>
#include <vector>
#include <set>
#include <cfloat>
#include <cmath>
#include "xmath.h"

class ESeries
{
private:
    struct ESeriesComparer
    {
        using is_transparent = void;

        bool operator()(const ESeries &lhs, const ESeries &rhs) const { return lhs.GetName() < rhs.GetName(); }
        bool operator()(const std::string &lhs, const ESeries &rhs) const { return lhs < rhs.GetName(); }
        bool operator()(const ESeries &lhs, const std::string &rhs) const { return lhs.GetName() < rhs; }
        bool operator()(const std::string &lhs, const std::string &rhs) const { return lhs < rhs; }
    };

    static const std::set<ESeries, ESeriesComparer> k_StandardSeries;

    std::string m_Name;
    std::vector<double> m_Tolerances;
    std::vector<double> m_BaseResistances;

public:
    static double Standardize(const double res)
    {
        int lg = (int)floor(log10(res));
        return res / pow(10, lg);
    }

    static const ESeries *Find(const std::string name)
    {
        return Find(name.c_str());
    }

    static const ESeries *Find(const char *const name)
    {
        std::set<ESeries, ESeriesComparer>::const_iterator result = ESeries::k_StandardSeries.find(name);
        return result != k_StandardSeries.cend() ? &(*result) : nullptr;
    }

    static std::vector<double> CalculateSeries(const unsigned int n, const int e)
    {
        std::vector<double> result;
        double multiplier = pow(10.0, e);
        for(unsigned int i = 0; i < n; i++)
        {
            result.push_back(round(multiplier * pow(10.0, (double)i / (double)n)));
        }

        return result;
    }

    std::string GetName(void) const { return m_Name; }

    double GetTolerance(void) const
    {
        return m_Tolerances.front();
    }

    double GetTolerance(const double value) const
    {
        for(size_t i = m_Tolerances.size() - 1U; i-- > 0U;)
        {
            if(m_Tolerances[i] <= value)
            {
                return m_Tolerances[i];
            }
        }

        return 0.0;
    }

    double GetBaseResistance(const double value) const
    {
        double result = -1.0;
        FindBaseResistance(ESeries::Standardize(value), result);
        return result;
    }

    bool FindBaseResistance(const double value, double &result) const
    {
        if(value < m_BaseResistances.front())
        {
            result = m_BaseResistances.front();
            return true;
        }
        else if(value > m_BaseResistances.back())
        {
            result = m_BaseResistances.back();
            return true;
        }

        for(size_t i = 0U; i < m_BaseResistances.size(); i++)
        {
            if(m_BaseResistances[i] >= value - DBL_EPSILON)
            {
                result = m_BaseResistances[i];
                return true;
            }
        }

        return false;
    }

    ESeries(const std::string &name, const std::vector<double> &tolerances, const std::vector<double> &values)
    {
        m_Name = name;
        m_Tolerances = tolerances;
        m_BaseResistances = values;
    }
};

#endif // _ESERIES_HPP_