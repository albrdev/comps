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
    static double Standardize(const double res);
    static const ESeries *Find(const std::string name);
    static const ESeries *Find(const char *const name);

    static std::vector<double> CalculateSeries(const unsigned int n, const int e);

    std::string GetName(void) const;
    double GetTolerance(void) const;
    double GetTolerance(const double value) const;
    double GetBaseResistance(const double value) const;

    bool FindBaseResistance(const double value, double &result) const;

    ESeries(const std::string &name, const std::vector<double> &tolerances, const std::vector<double> &values);
};

#endif // _ESERIES_HPP_
