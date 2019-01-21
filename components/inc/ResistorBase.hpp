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

protected:
    ResistorBase(const bool autoID = true);

public:
    static double CombinedResistance(const std::vector<std::shared_ptr<ResistorBase>> &resistors, const CircuitConnectionType circuitType);
    static double CombinedMinResistance(const std::vector<std::shared_ptr<ResistorBase>> &resistors, const CircuitConnectionType circuitType);
    static double CombinedMaxResistance(const std::vector<std::shared_ptr<ResistorBase>> &resistors, const CircuitConnectionType circuitType);

    double GetResistance(void) const;
    double GetResistance(const std::string &symbol) const;
    virtual void SetResistance(const double value);

    double GetMinResistance(void) const;
    double GetMinResistance(const std::string &symbol) const;
    double GetMaxResistance(void) const;
    double GetMaxResistance(const std::string &symbol) const;

    virtual double GetTolerance(void) const = 0;

    std::string ToString(const std::string &symbol) const;
    std::string ToString(void) const override;

    ResistorBase(const double resistance, const bool autoID = true);
};

#endif // _RESISTORBASE_HPP_
