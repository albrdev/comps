#include "ResistorBase.hpp"

double ResistorBase::CombinedResistance(const std::vector<std::shared_ptr<ResistorBase>> &resistors, const CircuitConnectionType circuitType)
{
    double result = 0.0;
    switch(circuitType)
    {
        case CircuitConnectionType::CCT_SERIAL:
            for(size_t i = 0U; i < resistors.size(); i++)
            {
                result += resistors[i]->GetResistance();
            }

            return result;

        case CircuitConnectionType::CCT_PARALLEL:
            for(size_t i = 0U; i < resistors.size(); i++)
            {
                result += 1.0 / resistors[i]->GetResistance();
            }

            return 1.0 / result;

        default:
            throw;
    }
}

double ResistorBase::CombinedMinResistance(const std::vector<std::shared_ptr<ResistorBase>> &resistors, const CircuitConnectionType circuitType)
{
    double result = 0.0;
    switch(circuitType)
    {
        case CircuitConnectionType::CCT_SERIAL:
            for(size_t i = 0U; i < resistors.size(); i++)
            {
                result += resistors[i]->GetMinResistance();
            }

            return result;

        case CircuitConnectionType::CCT_PARALLEL:
            for(size_t i = 0U; i < resistors.size(); i++)
            {
                result += 1.0 / resistors[i]->GetMinResistance();
            }

            return 1.0 / result;

        default:
            throw;
    }
}

double ResistorBase::CombinedMaxResistance(const std::vector<std::shared_ptr<ResistorBase>> &resistors, const CircuitConnectionType circuitType)
{
    double result = 0.0;
    switch(circuitType)
    {
        case CircuitConnectionType::CCT_SERIAL:
            for(size_t i = 0U; i < resistors.size(); i++)
            {
                result += resistors[i]->GetMaxResistance();
            }

            return result;

        case CircuitConnectionType::CCT_PARALLEL:
            for(size_t i = 0U; i < resistors.size(); i++)
            {
                result += 1.0 / resistors[i]->GetMaxResistance();
            }

            return 1.0 / result;

        default:
            throw;
    }
}

double ResistorBase::GetResistance(void) const { return m_Resistance; }
double ResistorBase::GetResistance(const std::string &symbol) const { return GetResistance() / Prefix::GetMultiplier(symbol); }
void ResistorBase::SetResistance(const double value) { m_Resistance = value; }

double ResistorBase::GetMinResistance() const { return GetResistance() * (1.0 - GetTolerance()); }
double ResistorBase::GetMinResistance(const std::string &symbol) const { return GetMinResistance() / Prefix::GetMultiplier(symbol); }
double ResistorBase::GetMaxResistance() const { return GetResistance() * (1.0 + GetTolerance()); }
double ResistorBase::GetMaxResistance(const std::string &symbol) const { return GetMaxResistance() / Prefix::GetMultiplier(symbol); }

std::string ResistorBase::ToString(const std::string &symbol) const
{
    std::ostringstream oss;
    oss << GetResistance(symbol) << symbol << ", " << dectopc(GetTolerance()) << '%';
    return oss.str();
}

std::string ResistorBase::ToString() const
{
    std::ostringstream oss;
    oss << GetResistance() << ", " << dectopc(GetTolerance()) << '%';
    return oss.str();
}

ResistorBase::ResistorBase(const double resistance, const bool autoID) : Component(autoID)
{
    SetResistance(resistance);
}
