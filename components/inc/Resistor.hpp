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
    double m_Tolerance;
    std::string m_ESeriesName;

public:
    static Resistor Combine(const std::vector<Resistor> &resistors, const std::string &eSeriesName, const CircuitConnectionType circuitType)
    {
        return Combine(resistors, NumberSeries::Find(eSeriesName), circuitType);
    }

    static Resistor Combine(const std::vector<Resistor> &resistors, const NumberSeries *const eSeries, const CircuitConnectionType circuitType)
    {
        if(eSeries == nullptr)
            throw;

        switch(circuitType)
        {
            case CircuitConnectionType::CCT_SERIAL:
                return Resistor(CombinedResistance(resistors, circuitType), eSeries);

            case CircuitConnectionType::CCT_PARALLEL:
                return Resistor(CombinedResistance(resistors, circuitType), eSeries);

            default:
                throw;
        }
    }

    static Resistor Combine(const std::vector<Resistor> &resistors, const double tolerance, const CircuitConnectionType circuitType)
    {
        switch(circuitType)
        {
            case CircuitConnectionType::CCT_SERIAL:
                return Resistor(CombinedResistance(resistors, circuitType), tolerance);

            case CircuitConnectionType::CCT_PARALLEL:
                return Resistor(CombinedResistance(resistors, circuitType), tolerance);

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
    double GetResistance(const std::string &symbol) const { return m_Resistance / Prefix::GetMultiplier(symbol); }
    void SetResistance(const double value) { m_Resistance = value; }

    double GetMinResistance() const { return GetResistance() * (1.0 - GetTolerance()); }
    double GetMaxResistance() const { return GetResistance() * (1.0 + GetTolerance()); }

    double GetTolerance(void) const { return m_Tolerance; }

    Resistor(double resistance, const std::string &eSeriesName, bool autoID = true) : Resistor(resistance, NumberSeries::Find(eSeriesName), autoID) { }

    Resistor(double resistance, const NumberSeries *const eSeries, bool autoID = true) : Component(0.0, autoID)
    {
        if(eSeries == nullptr)
            throw;

        m_ESeriesName = eSeries->GetName();

        double baseResistance = eSeries->GetBaseResistance(resistance);
        int exponent = Prefix::CalcExponent(resistance);
        m_Resistance = baseResistance * pow(10, exponent);
        m_Tolerance = eSeries->GetTolerance();
    }

    Resistor(double resistance, const double tolerance, bool autoID = true) : Component(0.0, autoID)
    {
        m_Resistance = resistance;
        m_Tolerance = tolerance;
    }
};

#endif // _RESISTOR_HPP_
