#include "StandardResistor.hpp"

double StandardResistor::FindUpperSuitableResistance(const double resistance, const NumberSeries *const eSeries)
{
    return eSeries->GetBaseResistance(resistance) * pow(10, Prefix::CalcExponent(resistance));
}

StandardResistor StandardResistor::Combine(const std::vector<std::shared_ptr<ResistorBase>> &resistors, const std::string &eSeriesName, const CircuitConnectionType circuitType)
{
    const NumberSeries *eSeries = NumberSeries::Find(eSeriesName);
    if(eSeries == nullptr)
        throw;

    return Combine(resistors, eSeries, circuitType);
}

StandardResistor StandardResistor::Combine(const std::vector<std::shared_ptr<ResistorBase>> &resistors, const NumberSeries *const eSeries, const CircuitConnectionType circuitType)
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

void StandardResistor::Set(const double resistance, const NumberSeries *const eSeries)
{
    if(eSeries == nullptr)
        throw;

    m_ESeries = eSeries;
    ResistorBase::SetResistance(FindUpperSuitableResistance(resistance, m_ESeries));
}

void StandardResistor::SetResistance(const double value) { Set(value, m_ESeries); }

double StandardResistor::GetTolerance(void) const { return m_ESeries->GetTolerance(); }

const NumberSeries *StandardResistor::GetESeries(void) const { return m_ESeries; }
void StandardResistor::SetESeries(const NumberSeries *const value) { Set(GetResistance(), value); }

std::string StandardResistor::ToString(void) const
{
    std::ostringstream oss;
    oss << ResistorBase::ToString() << ", " << m_ESeries->GetName();
    return oss.str();
}

StandardResistor::StandardResistor(double resistance, const std::string &eSeriesName, bool autoID) : StandardResistor(resistance, NumberSeries::Find(eSeriesName), autoID) { }

StandardResistor::StandardResistor(double resistance, const NumberSeries *const eSeries, bool autoID) : ResistorBase(autoID)
{
    Set(resistance, eSeries);
}
