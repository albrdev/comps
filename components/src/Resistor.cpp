#include "Resistor.hpp"
#include <algorithm>

const std::map<ResistorColorCode, Resistor::ColorData> Resistor::k_ColorData
{
    { ResistorColorCode::RCC_BLACK, Resistor::ColorData { 0, -1.0, "Black" } },
    { ResistorColorCode::RCC_BROWN, Resistor::ColorData { 1, 0.01, "Brown" } },
    { ResistorColorCode::RCC_RED, Resistor::ColorData { 2, 0.02, "Red" } },
    { ResistorColorCode::RCC_ORANGE, Resistor::ColorData { 3, -1.0, "Orange" } },
    { ResistorColorCode::RCC_YELLOW, Resistor::ColorData { 4, -1.0, "Yellow" } },
    { ResistorColorCode::RCC_GREEN, Resistor::ColorData { 5, 0.005, "Green" } },
    { ResistorColorCode::RCC_BLUE, Resistor::ColorData { 6, 0.0025, "Blue" } },
    { ResistorColorCode::RCC_PURPLE, Resistor::ColorData { 7, 0.001, "Purple" } },
    { ResistorColorCode::RCC_GRAY, Resistor::ColorData { 8, 0.0005, "Gray" } },
    { ResistorColorCode::RCC_WHITE, Resistor::ColorData { 9, -1.0, "White" } },
    { ResistorColorCode::RCC_GOLD, Resistor::ColorData { -1, 0.05, "Gold" } },
    { ResistorColorCode::RCC_SILVER, Resistor::ColorData { -2, 0.1, "Silver" } }
};

double Resistor::FindUpperSuitableResistance(const double resistance, const NumberSeries *const eSeries)
{
    return eSeries->GetBaseResistance(resistance) * pow(10, Prefix::CalcExponent(resistance));
}

// https://www.edaboard.com/showthread.php?283445-Total-resistance-tolerance-calculation
/*void Resistor::CombinedResistance(const std::vector<ResistorBase> &resistors, const CircuitConnectionType circuitType, double &resistance, double &tolerance)
{
    resistance = 0.0;
    tolerance = 0.0;
    switch(circuitType)
    {
        case CircuitConnectionType::CCT_SERIAL:
        {
            //(T1*R1+T2*R2)/(R1+R2)
            for(size_t i = 0U; i < resistors.size(); i++)
            {
                resistance += resistors[i].GetResistance();

                tolerance += resistors[i].GetTolerance() * resistors[i].GetResistance();
            }

            tolerance /= resistance;
            break;
        }

        case CircuitConnectionType::CCT_PARALLEL:
        {
            //(T1/R1+T2/R2)*(R1*R2)/(R1+R2)
            double sum = 0.0, product = 1.0;
            for(size_t i = 0U; i < resistors.size(); i++)
            {
                resistance += 1.0 / resistors[i].GetResistance();

                tolerance += resistors[i]->GetTolerance() / resistors[i].GetResistance();
                sum += resistors[i].GetResistance();
                product *= resistors[i].GetResistance();
            }

            resistance = 1.0 / resistance;
            tolerance *= (product / sum);
            break;
        }

        default:
            throw;
    }
}*/

/*Resistor Resistor::Combine(const std::vector<ResistorBase> &resistors, const CircuitConnectionType circuitType)
{
    double resistance = 0.0;
    double tolerance = 0.0;
    ResistorBase::CombinedResistance(resistors, circuitType, resistance, tolerance);
    return ResistorBase(resistance, tolerance);
}*/

Resistor Resistor::Combine(const std::vector<Resistor> &resistors, const double tolerance, const std::string &eSeriesName, const CircuitConnectionType circuitType)
{
    const NumberSeries *eSeries = NumberSeries::Find(eSeriesName);
    if(eSeries == nullptr)
        throw;

    return Combine(resistors, tolerance, eSeries, circuitType);
}

Resistor Resistor::Combine(const std::vector<Resistor> &resistors, const double tolerance, const NumberSeries *const eSeries, const CircuitConnectionType circuitType)
{
    switch(circuitType)
    {
        case CircuitConnectionType::CCT_SERIAL:
            return Resistor(Resistor::CombinedResistance(resistors, circuitType), tolerance, eSeries);

        case CircuitConnectionType::CCT_PARALLEL:
            return Resistor(Resistor::CombinedResistance(resistors, circuitType), tolerance, eSeries);

        default:
            throw;
    }
}

Resistor Resistor::Combine(const std::vector<Resistor> &resistors, const double tolerance, const CircuitConnectionType circuitType)
{
    switch(circuitType)
    {
        case CircuitConnectionType::CCT_SERIAL:
            return Resistor(Resistor::CombinedResistance(resistors, circuitType), tolerance);

        case CircuitConnectionType::CCT_PARALLEL:
            return Resistor(Resistor::CombinedResistance(resistors, circuitType), tolerance);

        default:
            throw;
    }
}

double Resistor::CombinedResistance(const std::vector<Resistor> &resistors, const CircuitConnectionType circuitType)
{
    double result = 0.0;
    switch(circuitType)
    {
        case CircuitConnectionType::CCT_SERIAL:
        {
            for(size_t i = 0U; i < resistors.size(); i++)
            {
                result += resistors[i].GetResistance();
            }

            return result;
        }

        case CircuitConnectionType::CCT_PARALLEL:
        {
            for(size_t i = 0U; i < resistors.size(); i++)
            {
                result += 1.0 / resistors[i].GetResistance();
            }

            return 1.0 / result;
        }

        default:
            throw;
    }
}

double Resistor::CombinedMinResistance(const std::vector<Resistor> &resistors, const CircuitConnectionType circuitType)
{
    double result = 0.0;
    switch(circuitType)
    {
        case CircuitConnectionType::CCT_SERIAL:
        {
            for(size_t i = 0U; i < resistors.size(); i++)
            {
                result += resistors[i].GetMinResistance();
            }

            return result;
        }

        case CircuitConnectionType::CCT_PARALLEL:
        {
            for(size_t i = 0U; i < resistors.size(); i++)
            {
                result += 1.0 / resistors[i].GetMinResistance();
            }

            return 1.0 / result;
        }

        default:
            throw;
    }
}

double Resistor::CombinedMaxResistance(const std::vector<Resistor> &resistors, const CircuitConnectionType circuitType)
{
    double result = 0.0;
    switch(circuitType)
    {
        case CircuitConnectionType::CCT_SERIAL:
        {
            for(size_t i = 0U; i < resistors.size(); i++)
            {
                result += resistors[i].GetMaxResistance();
            }

            return result;
        }

        case CircuitConnectionType::CCT_PARALLEL:
        {
            for(size_t i = 0U; i < resistors.size(); i++)
            {
                result += 1.0 / resistors[i].GetMaxResistance();
            }

            return 1.0 / result;
        }

        default:
            throw;
    }
}

/*double ResistorBase::CombinedTolerance(const std::vector<ResistorBase> &resistors)
{
    double result = 0.0;
    for(size_t i = 0U; i < resistors.size(); i++)
    {
        result += resistors[i].GetTolerance();
    }

    return result / (double)resistors.size();
}*/

double Resistor::GetResistance(void) const { return m_Resistance; }
double Resistor::GetResistance(const std::string &symbol) const { return GetResistance() / Prefix::GetMultiplier(symbol); }

double Resistor::GetMinResistance(void) const { return GetResistance() * (1.0 - GetTolerance()); }
double Resistor::GetMinResistance(const std::string &symbol) const { return GetMinResistance() / Prefix::GetMultiplier(symbol); }
double Resistor::GetMaxResistance(void) const { return GetResistance() * (1.0 + GetTolerance()); }
double Resistor::GetMaxResistance(const std::string &symbol) const { return GetMaxResistance() / Prefix::GetMultiplier(symbol); }

double Resistor::GetTolerance(void) const { return m_Tolerance; }

const NumberSeries *Resistor::GetESeries(void) const { return m_ESeries; }

std::string Resistor::GetColorString(const unsigned int resBands)
{
    int lg = (int)floor(log10(GetResistance()));
    double base = GetResistance() / pow(10, lg);

    std::ostringstream oss;
    std::map<ResistorColorCode, Resistor::ColorData>::const_iterator iter;
    for(unsigned int i = 0U; i < resBands - 1; i++)
    {
        iter = k_ColorData.find((ResistorColorCode)getdigit(base, i));
        oss << (iter != k_ColorData.cend() ? iter->second.Name : "n/a") << ' ';
    }

    iter = std::find_if(k_ColorData.cbegin(), k_ColorData.cend(), [value = lg - 1](const std::pair<ResistorColorCode, Resistor::ColorData> &e) { return e.second.Exponent == value; });
    oss << (iter != k_ColorData.cend() ? iter->second.Name : "n/a") << ' ';

    iter = std::find_if(k_ColorData.cbegin(), k_ColorData.cend(), [value = GetTolerance()](const std::pair<ResistorColorCode, Resistor::ColorData> &e) { return e.second.Tolerance == value; });
    oss << (iter != k_ColorData.cend() ? iter->second.Name : "n/a");

    return oss.str();
}

std::string Resistor::ToString(const std::string &symbol) const
{
    std::ostringstream oss;
    oss << GetResistance(symbol) << symbol << " (" << dectopc(GetTolerance()) << '%' << ", " << (m_ESeries != nullptr ? m_ESeries->GetName() : "") << ')';
    return oss.str();
}

std::string Resistor::ToString(void) const
{
    std::ostringstream oss;
    oss << GetResistance() << " (" << dectopc(GetTolerance()) << '%' << ", " << (m_ESeries != nullptr ? m_ESeries->GetName() : "") << ')';
    return oss.str();
}

Resistor::Resistor(const std::vector<std::string> &colorStrings, const std::string &eSeriesName, const bool autoID) : Resistor(colorStrings, NumberSeries::Find(eSeriesName), autoID) { }

Resistor::Resistor(const std::vector<std::string> &colorStrings, const char *const eSeriesName, const bool autoID) : Resistor(colorStrings, NumberSeries::Find(eSeriesName), autoID) { }

Resistor::Resistor(const std::vector<std::string> &colorStrings, const NumberSeries *const eSeries, const bool autoID) : Resistor(colorStrings, autoID)
{
    if(eSeries == nullptr || eSeries->GetBaseResistance(m_Resistance) < 0.0)
        throw;

    m_ESeries = eSeries;
}

Resistor::Resistor(const std::vector<std::string> &colorStrings, const bool autoID) : Component(autoID)
{
    if(colorStrings.size() < 3U || colorStrings.size() > 6U)
        throw;

    std::map<ResistorColorCode, Resistor::ColorData>::const_iterator iter;

    iter = std::find_if(k_ColorData.cbegin(), k_ColorData.cend(), [value = colorStrings[0]](const std::pair<ResistorColorCode, Resistor::ColorData> &e) { return e.second.Name == value; });
    if(iter == k_ColorData.cend()) throw;
    double base = iter->first;

    iter = std::find_if(k_ColorData.cbegin(), k_ColorData.cend(), [value = colorStrings[1]](const std::pair<ResistorColorCode, Resistor::ColorData> &e) { return e.second.Name == value; });
    if(iter == k_ColorData.cend()) throw;
    base = (base * 10.0) + iter->first;

    iter = std::find_if(k_ColorData.cbegin(), k_ColorData.cend(), [value = colorStrings[2]](const std::pair<ResistorColorCode, Resistor::ColorData> &e) { return e.second.Name == value; });
    if(iter == k_ColorData.cend()) throw;
    m_Resistance = base * pow(10.0, iter->second.Exponent);

    iter = std::find_if(k_ColorData.cbegin(), k_ColorData.cend(), [value = colorStrings[3]](const std::pair<ResistorColorCode, Resistor::ColorData> &e) { return e.second.Name == value; });
    if(iter == k_ColorData.cend()) throw;
    m_Tolerance = iter->second.Tolerance;
}

Resistor::Resistor(double resistance, const std::string &eSeriesName, bool autoID) : Resistor(resistance, NumberSeries::Find(eSeriesName), autoID) { }

Resistor::Resistor(double resistance, const char *const eSeriesName, bool autoID) : Resistor(resistance, NumberSeries::Find(eSeriesName), autoID) { }

Resistor::Resistor(double resistance, const NumberSeries *const eSeries, bool autoID) : Component(autoID)
{
    if(eSeries == nullptr)
        throw;

    m_ESeries = eSeries;

    m_Resistance = FindUpperSuitableResistance(resistance, m_ESeries);
    m_Tolerance = m_ESeries->GetTolerance();
}

Resistor::Resistor(double resistance, const double tolerance, const std::string &eSeriesName, bool autoID) : Resistor(resistance, tolerance, NumberSeries::Find(eSeriesName), autoID) { }

Resistor::Resistor(double resistance, const double tolerance, const char *const eSeriesName, bool autoID) : Resistor(resistance, tolerance, NumberSeries::Find(eSeriesName), autoID) { }

Resistor::Resistor(double resistance, const double tolerance, const NumberSeries *const eSeries, bool autoID) : Component(autoID)
{
    if(eSeries == nullptr)
        throw;

    m_ESeries = eSeries;

    m_Resistance = FindUpperSuitableResistance(resistance, m_ESeries);
    m_Tolerance = tolerance;
}

Resistor::Resistor(const double resistance, const double tolerance, const bool autoID) : Component(autoID)
{
    m_Resistance = resistance;
    m_Tolerance = tolerance;
}
