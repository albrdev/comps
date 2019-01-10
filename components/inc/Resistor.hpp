#ifndef _RESISTOR_HPP_
#define _RESISTOR_HPP_

#include <vector>
#include "Component.hpp"

class Resistor : public Component
{
private:
    double m_Tolerance;

public:
    static Resistor Combine(const std::vector<Resistor> &values, const bool isParallel)
    {
        return isParallel ? ParallelCombine(values) : SerialCombine(values);
    }

    static Resistor SerialCombine(const std::vector<Resistor> &values)
    {
        double result = 0.0;
        for(size_t i = 0; i < values.size(); i++)
        {
            result += values[i].GetResistance();
        }

        return Resistor(result, 0.05, 1.0); //
    }

    static Resistor ParallelCombine(const std::vector<Resistor> &values)
    {
        double result = 0.0;
        for(size_t i = 0; i < values.size(); i++)
        {
            result += 1.0 / values[i].GetResistance();
        }

        return Resistor(1.0 / result, 0.05, 1.0); //
    }

    double GetTolerance(void) const { return m_Tolerance; }
    void SetTolerance(const double value) { m_Tolerance = value; }

    double MinResistance() const { return GetResistance() - (GetResistance() * m_Tolerance); }
    double MaxResistance() const { return GetResistance() + (GetResistance() * m_Tolerance); }

    Resistor(double resistance, double tolerance, double maxEffect) : Component(resistance, maxEffect)
    {
        SetTolerance(tolerance);
    }
};

#endif // _RESISTOR_HPP_