#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <set>
#include <cmath>
#include <iomanip>
#include <regex>
#include "Resistor.hpp"
#include "NumberSeries.hpp"
#include "Prefix.hpp"

#define arraycount(arr) (sizeof(arr) / sizeof(*arr))

struct NumberSeriesCompare
{
    using is_transparent = void;

    bool operator()(const NumberSeries &lhs, const NumberSeries &rhs) const
    {
        return lhs.GetName() < rhs.GetName();
    }

    bool operator()(const std::string &lhs, const NumberSeries &rhs) const
    {
        return lhs < rhs.GetName();
    }

    bool operator()(const NumberSeries &lhs, const std::string &rhs) const
    {
        return lhs.GetName() < rhs;
    }

    bool operator()(const std::string &lhs, const std::string &rhs) const
    {
        return lhs < rhs;
    }
};

const std::set<NumberSeries, NumberSeriesCompare> ns
{
    { "E3", 0.2, { 1.0, 2.2, 4.7 } },
    { "E6", 0.2, { 1.0, 1.5, 2.2, 3.3, 4.7, 6.8 } },
    { "E12", 0.1, { 1.0, 1.2, 1.5, 1.8, 2.2, 2.7, 3.3, 3.9, 4.7, 5.6, 6.8, 8.2 } },
    { "E24", 0.05, { 1.0, 1.1, 1.2, 1.3, 1.5, 1.6, 1.8, 2.0, 2.2, 2.4, 2.7, 3.0, 3.3, 3.6, 3.9, 4.3, 4.7, 5.1, 5.6, 6.2, 6.8, 7.5, 8.2, 9.1 } },
    { "E48", 0.02, { 1.00, 1.05, 1.10, 1.15, 1.21, 1.27, 1.33, 1.40, 1.47, 1.54, 1.62, 1.69, 1.78, 1.87, 1.96, 2.05, 2.15, 2.26, 2.37, 2.49, 2.61, 2.74, 2.87, 3.01, 3.16, 3.32, 3.48, 3.65, 3.83, 4.02, 4.22, 4.42, 4.64, 4.87, 5.11, 5.36, 5.62, 5.90, 6.19, 6.49, 6.81, 7.15, 7.50, 7.87, 8.25, 8.66, 9.09, 9.53 } },
    { "E96", 0.01, { 1.00, 1.02, 1.05, 1.07, 1.10, 1.13, 1.15, 1.18, 1.21, 1.24, 1.27, 1.30, 1.33, 1.37, 1.40, 1.43, 1.47, 1.50, 1.54, 1.58, 1.62, 1.65, 1.69, 1.74, 1.78, 1.82, 1.87, 1.91, 1.96, 2.00, 2.05, 2.10, 2.15, 2.21, 2.26, 2.32, 2.37, 2.43, 2.49, 2.55, 2.61, 2.67, 2.74, 2.80, 2.87, 2.94, 3.01, 3.09, 3.16, 3.24, 3.32, 3.40, 3.48, 3.57, 3.65, 3.74, 3.83, 3.92, 4.02, 4.12, 4.22, 4.32, 4.42, 4.53, 4.64, 4.75, 4.87, 4.99, 5.11, 5.23, 5.36, 5.49, 5.62, 5.76, 5.90, 6.04, 6.19, 6.34, 6.49, 6.65, 6.81, 6.98, 7.15, 7.32, 7.50, 7.68, 7.87, 8.06, 8.25, 8.45, 8.66, 8.87, 9.09, 9.31, 9.53, 9.76 } },
    { "E192", 0.01, { 1.00, 1.01, 1.02, 1.04, 1.05, 1.06, 1.07, 1.09, 1.10, 1.11, 1.13, 1.14, 1.15, 1.17, 1.18, 1.20, 1.21, 1.23, 1.24, 1.26, 1.27, 1.29, 1.30, 1.32, 1.33, 1.35, 1.37, 1.38, 1.40, 1.42, 1.43, 1.45, 1.47, 1.49, 1.50, 1.52, 1.54, 1.56, 1.58, 1.60, 1.62, 1.64, 1.65, 1.67, 1.69, 1.72, 1.74, 1.76, 1.78, 1.80, 1.82, 1.84, 1.87, 1.89, 1.91, 1.93, 1.96, 1.98, 2.00, 2.03, 2.05, 2.08, 2.10, 2.13, 2.15, 2.18, 2.21, 2.23, 2.26, 2.29, 2.32, 2.34, 2.37, 2.40, 2.43, 2.46, 2.49, 2.52, 2.55, 2.58, 2.61, 2.64, 2.67, 2.71, 2.74, 2.77, 2.80, 2.84, 2.87, 2.91, 2.94, 2.98, 3.01, 3.05, 3.09, 3.12, 3.16, 3.20, 3.24, 3.28, 3.32, 3.36, 3.40, 3.44, 3.48, 3.52, 3.57, 3.61, 3.65, 3.70, 3.74, 3.79, 3.83, 3.88, 3.92, 3.97, 4.02, 4.07, 4.12, 4.17, 4.22, 4.27, 4.32, 4.37, 4.42, 4.48, 4.53, 4.59, 4.64, 4.70, 4.75, 4.81, 4.87, 4.93, 4.99, 5.05, 5.11, 5.17, 5.23, 5.30, 5.36, 5.42, 5.49, 5.56, 5.62, 5.69, 5.76, 5.83, 5.90, 5.97, 6.04, 6.12, 6.19, 6.26, 6.34, 6.42, 6.49, 6.57, 6.65, 6.73, 6.81, 6.90, 6.98, 7.06, 7.15, 7.23, 7.32, 7.41, 7.50, 7.59, 7.68, 7.77, 7.87, 7.96, 8.06, 8.16, 8.25, 8.35, 8.45, 8.56, 8.66, 8.76, 8.87, 8.98, 9.09, 9.20, 9.31, 9.42, 9.53, 9.65, 9.76, 9.88 } }
};

void Bla(void)
{
    for(std::set<NumberSeries, NumberSeriesCompare>::const_iterator i = ns.cbegin(); i != ns.cend(); i++)
    {
        std::cout << i->GetName() << std::endl;
    }
}

int knutmod(int a, int n)
{
    return a - (n * (int)floor((double)a / (double)n));
}

bool ParseResistor(const std::string &input, double &resistance, std::string &prefix, std::string &eSeries)
{
    std::regex regex(R"((-?[\d]+\.?[\d]*)([GMkmu]?),?\s*([eE][\d]+)?)");
    std::smatch match;
    if(!std::regex_match(input, match, regex))
        return false;

    if(match[1] == '\0')
        return false;

    resistance = strtod(match[1].str().c_str(), NULL);

    if(match[2] != '\0')
    {
        prefix = match[2];
    }

    if(match[3] != '\0')
    {
        eSeries = match[3];
    }

    return true;
}

int main(int argc, char *argv[])
{
    std::vector<Resistor> resistors;
    std::string input;
    CircuitConnectionType cct;

    if(argc < 3)
    {
        std::cout << "Insufficient arguments" << std::endl;
        return 1;
    }

    if(strcmp(argv[1], "-s") == 0)
    {
        cct = CircuitConnectionType::CCT_SERIAL;
    }
    else if(strcmp(argv[1], "-p") == 0)
    {
        cct = CircuitConnectionType::CCT_PARALLEL;
    }
    else
    {
        std::cout << "Invalid circuit connection specified" << std::endl;
        return 1;
    }

    std::set<NumberSeries, NumberSeriesCompare>::const_iterator eSeriesDefault = ns.find("E24");
    std::set<NumberSeries, NumberSeriesCompare>::const_iterator eSeries;

    for(int i=2; i<argc; i++)
    {
        if(*argv[i] == '\0') continue;

        double resistance;
        std::string prefix;
        std::string series;
        if(!ParseResistor(argv[i], resistance, prefix, series))
        {
            std::cout << "Invalid input" << std::endl;
            return 2;
        }

        Prefix::Apply(prefix, resistance);

        eSeries = series.empty() ? eSeriesDefault : ns.find(series);
        if(eSeries == ns.cend())
        {
            std::cout << "Invalid E series \'" << series << "\'" << std::endl;
            return 3;
        }

        // Create a new resistor and put it in the vector
        resistors.push_back(Resistor(resistance, *eSeries, 0.0));
    }

    for(size_t i = 0U; i < resistors.size(); i++)
    {
        printf("Resistor[%zu]: Resistance=%lf, Tolerance=%lf\n", i, resistors[i].GetResistance(), resistors[i].GetTolerance());
    }

    double res = Resistor::CombinedResistance(resistors, cct);
    double min = Resistor::CombinedMinResistance(resistors, cct);
    double max = Resistor::CombinedMaxResistance(resistors, cct);
    std::cout << "Total resistance: " << res << std::endl;
    std::cout << "Total min. resistance: " << min << std::endl;
    std::cout << "Total max. resistance: " << max << std::endl;
    std::cout << "Tolerance: " << eSeries->GetTolerance() << std::endl;

    double baseResistance = eSeries->Find(res);
    std::cout << "Value to search a standard E-number for: " << NumberSeries::Standardize(res) << std::endl;
    std::cout << "Standard E-number found: " << baseResistance << std::endl;

    int exponent = Prefix::CalcExponent(res);
    Resistor substitute(res, *eSeries, 0.0);
    std::cout << "Exponent: " << exponent << std::endl;

    int mod = knutmod(exponent, 3);
    if(mod == 1) exponent--;
    else if(mod == 2) exponent++;

    std::cout << "Exponent: " << exponent << std::endl;

    std::string symbol = Prefix::GetSymbol(exponent);
    std::cout << "Substitute resistor: " << substitute.GetResistance(symbol) << symbol << std::endl;

    return 0;
}
