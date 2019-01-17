#ifndef _RESISTOR_HPP_
#define _RESISTOR_HPP_

#include "Component.hpp"
#include "NumberSeries.hpp"
#include "Prefix.hpp"

enum CircuitConnectionType
{
    CCT_SERIAL = 1,
    CCT_PARALLEL = 2
};

class Resistor : public Component
{
private:
    double m_Resistance;
    const NumberSeries &m_ESeries;

public:
    static Resistor Combine(const std::vector<Resistor> &resistors, const NumberSeries &series, const CircuitConnectionType circuitType)
    {
        double result = 0.0;
        switch(circuitType)
        {
            case CircuitConnectionType::CCT_SERIAL:
                for(size_t i = 0; i < resistors.size(); i++)
                {
                    result += resistors[i].GetResistance();
                }

                return Resistor(result, series, 0.0);//*

            case CircuitConnectionType::CCT_PARALLEL:
                for(size_t i = 0; i < resistors.size(); i++)
                {
                    result += 1.0 / resistors[i].GetResistance();
                }

                return Resistor(1.0 / result, series, 0.0);//*

            default:
                throw;
        }
    }

    static double CombinedResistance(const std::vector<Resistor> &resistors, const CircuitConnectionType circuitType)
    {
        double result = 0.0;
        switch(circuitType)
        {
            case CircuitConnectionType::CCT_SERIAL:
                for(size_t i = 0U; i < resistors.size(); i++)
                {
                    result += resistors[i].GetResistance();
                }

                return result;

            case CircuitConnectionType::CCT_PARALLEL:
                for(size_t i = 0U; i < resistors.size(); i++)
                {
                    result += 1.0 / resistors[i].GetResistance();
                }

                return 1.0 / result;

            default:
                throw;
        }
    }

    static double CombinedMinResistance(const std::vector<Resistor> &resistors, const CircuitConnectionType circuitType)
    {
        double result = 0.0;
        switch(circuitType)
        {
            case CircuitConnectionType::CCT_SERIAL:
                for(size_t i = 0U; i < resistors.size(); i++)
                {
                    result += resistors[i].GetMinResistance();
                }

                return result;

            case CircuitConnectionType::CCT_PARALLEL:
                for(size_t i = 0U; i < resistors.size(); i++)
                {
                    result += 1.0 / resistors[i].GetMinResistance();
                }

                return 1.0 / result;

            default:
                throw;
        }
    }

    static double CombinedMaxResistance(const std::vector<Resistor> &resistors, const CircuitConnectionType circuitType)
    {
        double result = 0.0;
        switch(circuitType)
        {
            case CircuitConnectionType::CCT_SERIAL:
                for(size_t i = 0U; i < resistors.size(); i++)
                {
                    result += resistors[i].GetMaxResistance();
                }

                return result;

            case CircuitConnectionType::CCT_PARALLEL:
                for(size_t i = 0U; i < resistors.size(); i++)
                {
                    result += 1.0 / resistors[i].GetMaxResistance();
                }

                return 1.0 / result;

            default:
                throw;
        }
    }

    double GetResistance(void) const { return m_Resistance; }
    void SetResistance(const double value) { m_Resistance = value; }

    double GetResistance(const std::string &symbol) const
    {
        return m_Resistance / Prefix::GetMultiplier(symbol);
    }

    double GetMinResistance() const { return GetResistance() * (1.0 - GetTolerance()); }
    double GetMaxResistance() const { return GetResistance() * (1.0 + GetTolerance()); }

    double GetTolerance(void) const { return m_ESeries.GetTolerance(); }

    Resistor(double resistance, const NumberSeries &series, double maxEffect, bool autoID = true) : Component(maxEffect, autoID), m_ESeries(series)
    {
        double baseResistance = m_ESeries.Find(resistance);

        int exponent = Prefix::CalcExponent(resistance);
        m_Resistance = baseResistance * pow(10, exponent);
    }
};

#endif // _RESISTOR_HPP_
