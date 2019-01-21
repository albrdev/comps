#ifndef _RESISTORBASE_HPP_
#define _RESISTORBASE_HPP_

#include <string>
#include <sstream>
#include <memory>
#include "Component.hpp"
#include "NumberSeries.hpp"
#include "Prefix.hpp"
#include "xmath.h"

class ResistorBase : public Component
{
private:
    double m_Resistance;

public:
    static double CombinedResistance(const std::vector<std::shared_ptr<ResistorBase>> &resistors, const CircuitConnectionType circuitType)
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

    static double CombinedMinResistance(const std::vector<std::shared_ptr<ResistorBase>> &resistors, const CircuitConnectionType circuitType)
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

    static double CombinedMaxResistance(const std::vector<std::shared_ptr<ResistorBase>> &resistors, const CircuitConnectionType circuitType)
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

    double GetResistance(void) const { return m_Resistance; }
    double GetResistance(const std::string &symbol) const { return GetResistance() / Prefix::GetMultiplier(symbol); }
    void SetResistance(const double value) { m_Resistance = value; }

    double GetMinResistance() const { return GetResistance() * (1.0 - GetTolerance()); }
    double GetMinResistance(const std::string &symbol) const { return GetMinResistance() / Prefix::GetMultiplier(symbol); }
    double GetMaxResistance() const { return GetResistance() * (1.0 + GetTolerance()); }
    double GetMaxResistance(const std::string &symbol) const { return GetMaxResistance() / Prefix::GetMultiplier(symbol); }

    virtual double GetTolerance(void) const = 0;

    std::string ToString(const std::string &symbol) const
    {
        std::ostringstream oss;
        oss << GetResistance(symbol) << symbol << ", " << dectopc(GetTolerance()) << '%';
        return oss.str();
    }

    std::string ToString() const override
    {
        std::ostringstream oss;
        oss << GetResistance() << ", " << dectopc(GetTolerance()) << '%';
        return oss.str();
    }

    ResistorBase(const double resistance, const bool autoID = true) : Component(autoID)
    {
        m_Resistance = resistance;
    }
};

#endif // _RESISTORBASE_HPP_
