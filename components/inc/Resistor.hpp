#ifndef _RESISTOR_HPP_
#define _RESISTOR_HPP_

#include <string>
#include <map>
#include <sstream>
#include <memory>
#include "Component.hpp"
#include "ESeries.hpp"
#include "Prefix.hpp"
#include "xmath.h"

enum ResistorColorCode
{
    RCC_BLACK = 0,
    RCC_BROWN = 1,
    RCC_RED = 2,
    RCC_ORANGE = 3,
    RCC_YELLOW = 4,
    RCC_GREEN = 5,
    RCC_BLUE = 6,
    RCC_PURPLE = 7,
    RCC_GRAY = 8,
    RCC_WHITE = 9,
    RCC_GOLD = 10,
    RCC_SILVER = 11
};

class Resistor : public Component
{
private:
    struct ColorData
    {
        int Exponent;
        double Tolerance;
        char Name[8];
    };

    static const std::map<ResistorColorCode, Resistor::ColorData> k_ColorData;

    double m_Resistance = 0.0;
    double m_Tolerance = 0.0;

    const ESeries *m_ESeries = nullptr;

    static double FindUpperSuitableResistance(const double resistance, const ESeries *const eSeries);

public:
    //static void CombinedResistance(const std::vector<ResistorBase> &resistors, const CircuitConnectionType circuitType, double &resistance, double &tolerance);
    //static Resistor Combine(const std::vector<ResistorBase> &resistors, const CircuitConnectionType circuitType);

    static Resistor Combine(const std::vector<Resistor> &resistors, const double tolerance, const std::string &eSeriesName, const CircuitConnectionType circuitType);
    static Resistor Combine(const std::vector<Resistor> &resistors, const double tolerance, const ESeries *const eSeries, const CircuitConnectionType circuitType);
    static Resistor Combine(const std::vector<Resistor> &resistors, const double tolerance, const CircuitConnectionType circuitType);

    static double CombinedResistance(const std::vector<Resistor> &resistors, const CircuitConnectionType circuitType);
    static double CombinedMinResistance(const std::vector<Resistor> &resistors, const CircuitConnectionType circuitType);
    static double CombinedMaxResistance(const std::vector<Resistor> &resistors, const CircuitConnectionType circuitType);
    //static double CombinedTolerance(const std::vector<ResistorBase> &resistors);

    double GetResistance(void) const;
    double GetResistance(const std::string &symbol) const;

    double GetMinResistance(void) const;
    double GetMinResistance(const std::string &symbol) const;
    double GetMaxResistance(void) const;
    double GetMaxResistance(const std::string &symbol) const;

    double GetTolerance(void) const;

    const ESeries *GetESeries(void) const;

    std::string GetColorString(const unsigned int resBands);

    Resistor operator+(const Resistor &rhv)
    {
        return Resistor(GetResistance() + rhv.GetResistance(), (GetTolerance() + rhv.GetTolerance()) / 2.0);
    }

    Resistor operator*(const Resistor &rhv)
    {
        return Resistor(1.0 / ((1.0 / GetResistance()) + (1.0 / rhv.GetResistance())), (GetTolerance() + rhv.GetTolerance()) / 2.0);
    }

    std::string ToString(const std::string &symbol) const;
    std::string ToString(void) const override;

    Resistor(const std::vector<std::string> &colorStrings, const std::string &eSeriesName, const bool autoID = true);
    Resistor(const std::vector<std::string> &colorStrings, const char *const eSeriesName, const bool autoID = true);
    Resistor(const std::vector<std::string> &colorStrings, const ESeries *const eSeries, const bool autoID = true);
    Resistor(const std::vector<std::string> &colorStrings, const bool autoID = true);

    Resistor(double resistance, const std::string &eSeriesName, bool autoID = true);
    Resistor(double resistance, const char *const eSeriesName, bool autoID = true);
    Resistor(double resistance, const ESeries *const eSeries, bool autoID = true);

    Resistor(double resistance, const double tolerance, const std::string &eSeriesName, bool autoID = true);
    Resistor(double resistance, const double tolerance, const char *const eSeriesName, bool autoID = true);
    Resistor(double resistance, const double tolerance, const ESeries *const eSeries, bool autoID = true);

    Resistor(const double resistance, const double tolerance, const bool autoID = true);
};

#endif // _RESISTOR_HPP_
