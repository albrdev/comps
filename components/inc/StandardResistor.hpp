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

    static double FindUpperSuitableResistance(const double resistance, const NumberSeries &eSeries);

public:
    static StandardResistor Combine(const std::vector<std::shared_ptr<ResistorBase>> &resistors, const std::string &eSeriesName, const CircuitConnectionType circuitType);
    static StandardResistor Combine(const std::vector<std::shared_ptr<ResistorBase>> &resistors, const NumberSeries &eSeries, const CircuitConnectionType circuitType);

    double GetTolerance(void) const override;
    const NumberSeries &GetESeries(void) const;

    std::string ToString() const override;

    StandardResistor(double resistance, const std::string &eSeriesName, bool autoID = true);

    StandardResistor(double resistance, const NumberSeries &eSeries, bool autoID = true);
};

#endif // _STANDARDRESISTOR_HPP_
