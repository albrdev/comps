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
    static Resistor Combine(const std::vector<std::shared_ptr<ResistorBase>> &resistors, const double tolerance, const CircuitConnectionType circuitType);

    double GetTolerance(void)const override;
    void SetTolerance(const double value);

    Resistor(const double resistance, const double tolerance, bool autoID = true);
};

#endif // _RESISTOR_HPP_
