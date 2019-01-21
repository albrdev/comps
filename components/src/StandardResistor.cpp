#include "StandardResistor.hpp"

double StandardResistor::FindUpperSuitableResistance(const double resistance, const NumberSeries &eSeries)
{
    return eSeries.GetBaseResistance(resistance) * pow(10, Prefix::CalcExponent(resistance));
}

StandardResistor StandardResistor::Combine(const std::vector<std::shared_ptr<ResistorBase>> &resistors, const std::string &eSeriesName, const CircuitConnectionType circuitType)
{
    const NumberSeries *eSeries = NumberSeries::Find(eSeriesName);
    if(eSeries == nullptr)
        throw;

    return Combine(resistors, *eSeries, circuitType);
}

StandardResistor StandardResistor::Combine(const std::vector<std::shared_ptr<ResistorBase>> &resistors, const NumberSeries &eSeries, const CircuitConnectionType circuitType)
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

double StandardResistor::GetTolerance(void) const { return m_ESeries.GetTolerance(); }
const NumberSeries &StandardResistor::GetESeries(void) const { return m_ESeries; }

std::string StandardResistor::ToString() const
{
    std::ostringstream oss;
    oss << ResistorBase::ToString() << ", " << m_ESeries.GetName();
    return oss.str();
}

StandardResistor::StandardResistor(double resistance, const std::string &eSeriesName, bool autoID) : StandardResistor(resistance, *NumberSeries::Find(eSeriesName), autoID) { }

StandardResistor::StandardResistor(double resistance, const NumberSeries &eSeries, bool autoID) : ResistorBase(FindUpperSuitableResistance(resistance, eSeries), autoID), m_ESeries(eSeries) { }
