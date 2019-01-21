#include "Resistor.hpp"

Resistor Resistor::Combine(const std::vector<std::shared_ptr<ResistorBase>> &resistors, const double tolerance, const CircuitConnectionType circuitType)
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

double Resistor::GetTolerance(void) const { return m_Tolerance; }
void Resistor::SetTolerance(const double value) { m_Tolerance = value; }

Resistor::Resistor(const double resistance, const double tolerance, bool autoID) : ResistorBase(resistance, autoID)
{
    SetTolerance(tolerance);
}
