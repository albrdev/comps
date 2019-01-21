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
    const NumberSeries *m_ESeries;

    static double FindUpperSuitableResistance(const double resistance, const NumberSeries *const eSeries);

public:
    static StandardResistor Combine(const std::vector<std::shared_ptr<ResistorBase>> &resistors, const std::string &eSeriesName, const CircuitConnectionType circuitType);
    static StandardResistor Combine(const std::vector<std::shared_ptr<ResistorBase>> &resistors, const NumberSeries *const eSeries, const CircuitConnectionType circuitType);

    void Set(const double resistance, const NumberSeries *const eSeries);

    void SetResistance(const double value) override;

    double GetTolerance(void) const override;

    const NumberSeries *GetESeries(void) const;
    void SetESeries(const NumberSeries *const value);

    std::string ToString(void) const override;

    StandardResistor(double resistance, const std::string &eSeriesName, bool autoID = true);

    StandardResistor(double resistance, const NumberSeries *const eSeries, bool autoID = true);
};

#endif // _STANDARDRESISTOR_HPP_
