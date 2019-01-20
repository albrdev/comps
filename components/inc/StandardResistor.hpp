#ifndef _STANDARDRESISTOR_HPP_
#define _STANDARDRESISTOR_HPP_

#include <string>
#include <sstream>
#include <memory>
#include "ResistorBase.hpp"
#include "NumberSeries.hpp"
#include "Prefix.hpp"

class StandardResistor : public ResistorBase
{
private:
    const NumberSeries &m_ESeries;

    static double FindUpperSuitableResistance(const double resistance, const NumberSeries &eSeries)
    {
        return eSeries.GetBaseResistance(resistance) * pow(10, Prefix::CalcExponent(resistance));
    }

public:
    static StandardResistor Combine(const std::vector<std::shared_ptr<ResistorBase>> &resistors, const std::string &eSeriesName, const CircuitConnectionType circuitType)
    {
        const NumberSeries *eSeries = NumberSeries::Find(eSeriesName);
        if(eSeries == nullptr)
            throw;

        return Combine(resistors, *eSeries, circuitType);
    }

    static StandardResistor Combine(const std::vector<std::shared_ptr<ResistorBase>> &resistors, const NumberSeries &eSeries, const CircuitConnectionType circuitType)
    {
        switch(circuitType)
        {
            case CircuitConnectionType::CCT_SERIAL:
                return StandardResistor(ResistorBase::CombinedResistance(resistors, circuitType), eSeries);

            case CircuitConnectionType::CCT_PARALLEL:
                return StandardResistor(ResistorBase::CombinedResistance(resistors, circuitType), eSeries);

            default:
                throw;
        }
    }

    double GetTolerance(void) const override { return m_ESeries.GetTolerance(); }
    const NumberSeries &GetESeries(void) const { return m_ESeries; }

    std::string ToString() const override
    {
        std::ostringstream oss;
        oss << ResistorBase::ToString() << ", " << m_ESeries.GetName();
        return oss.str();
    }

    StandardResistor(double resistance, const std::string &eSeriesName, bool autoID = true) : StandardResistor(resistance, *NumberSeries::Find(eSeriesName), autoID) { }

    StandardResistor(double resistance, const NumberSeries &eSeries, bool autoID = true) : ResistorBase(FindUpperSuitableResistance(resistance, eSeries), autoID), m_ESeries(eSeries) { }
};

#endif // _STANDARDRESISTOR_HPP_
