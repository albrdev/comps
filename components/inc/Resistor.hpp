#ifndef _RESISTOR_HPP_
#define _RESISTOR_HPP_

#include <string>
#include <sstream>
#include <memory>
#include "ResistorBase.hpp"
#include "NumberSeries.hpp"
#include "Prefix.hpp"

class Resistor : public ResistorBase
{
private:
    double m_Tolerance;

public:
    static Resistor Combine(const std::vector<std::shared_ptr<ResistorBase>> &resistors, const double tolerance, const CircuitConnectionType circuitType)
    {
        switch(circuitType)
        {
            case CircuitConnectionType::CCT_SERIAL:
                return Resistor(ResistorBase::CombinedResistance(resistors, circuitType), tolerance);

            case CircuitConnectionType::CCT_PARALLEL:
                return Resistor(ResistorBase::CombinedResistance(resistors, circuitType), tolerance);

            default:
                throw;
        }
    }

    double GetTolerance(void) const override { return m_Tolerance; }

    Resistor(const double resistance, const double tolerance, bool autoID = true) : ResistorBase(resistance, autoID)
    {
        m_Tolerance = tolerance;
    }
};

#endif // _RESISTOR_HPP_
