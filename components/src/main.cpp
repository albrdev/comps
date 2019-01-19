#include <iostream>
#include <sstream>
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
#include "xmath.h"

#define arraycount(arr) (sizeof(arr) / sizeof(*arr))

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

std::map<double, ResistorColorCode> ColorNames3
{
    { 0.01, ResistorColorCode::RCC_BROWN },
    { 0.02, ResistorColorCode::RCC_RED },

    { 0.005, ResistorColorCode::RCC_GREEN },
    { 0.0025, ResistorColorCode::RCC_BLUE },
    { 0.001, ResistorColorCode::RCC_PURPLE },
    { 0.0005, ResistorColorCode::RCC_GRAY },

    { 0.05, ResistorColorCode::RCC_GOLD },
    { 0.1, ResistorColorCode::RCC_SILVER }
};

std::map<int, ResistorColorCode> ColorNames2
{
    { 0, ResistorColorCode::RCC_BLACK },
    { 1, ResistorColorCode::RCC_BROWN },
    { 2, ResistorColorCode::RCC_RED },
    { 3, ResistorColorCode::RCC_ORANGE },
    { 4, ResistorColorCode::RCC_YELLOW },
    { 5, ResistorColorCode::RCC_GREEN },
    { 6, ResistorColorCode::RCC_BLUE },
    { 7, ResistorColorCode::RCC_PURPLE },
    { 8, ResistorColorCode::RCC_GRAY },
    { 9, ResistorColorCode::RCC_WHITE },
    { -1, ResistorColorCode::RCC_GOLD },
    { -2, ResistorColorCode::RCC_SILVER }
};

std::map<ResistorColorCode, std::string> ColorNames
{
    { ResistorColorCode::RCC_BLACK, "Black" },
    { ResistorColorCode::RCC_BROWN, "Brown" },
    { ResistorColorCode::RCC_RED, "Red" },
    { ResistorColorCode::RCC_ORANGE, "Orange" },
    { ResistorColorCode::RCC_YELLOW, "Yellow" },
    { ResistorColorCode::RCC_GREEN, "Green" },
    { ResistorColorCode::RCC_BLUE, "Blue" },
    { ResistorColorCode::RCC_PURPLE, "Purple" },
    { ResistorColorCode::RCC_GRAY, "Gray" },
    { ResistorColorCode::RCC_WHITE, "White" },
    { ResistorColorCode::RCC_GOLD, "Gold" },
    { ResistorColorCode::RCC_SILVER, "Silver" }
};

class ResistorAttribute
{
};

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

std::string ColorString(const Resistor &resistor, const unsigned int resBands)
{
    int lg = (int)floor(log10(resistor.GetResistance()));
    double base = resistor.GetResistance() / pow(10, lg);

    std::ostringstream oss;
    for(unsigned int i = 0U; i < resBands - 1; i++)
    {
        oss << ColorNames[(ResistorColorCode)getdigit(base, i)] << ' ';
    }

    oss << ColorNames[ColorNames2[lg - 1]] << ' ';
    oss << ColorNames[ColorNames3[resistor.GetTolerance()]];

    return oss.str();
}

std::streamsize prec;
std::ios_base::fmtflags fmtflags;
void setp(const std::streamsize precision)
{
    prec = std::cout.precision(precision);
    //fmtflags = std::cout.flags(std::ios::fixed);
}

int main(int argc, char *argv[])
{
    std::vector<Resistor> resistors;
    std::string input;
    CircuitConnectionType cct;

    setp(2);

    if(argc < 3)
    {
        std::cout << "Usage: components -{s|p} resistance[prefix]..." << std::endl;
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

    const NumberSeries *eSeriesDefault = NumberSeries::Find("E24");
    const NumberSeries *eSeries;

    for(int i=2; i<argc; i++)
    {
        if(*argv[i] == '\0') continue;

        double resistance;
        std::string prefix;
        std::string eSeriesName;
        if(!ParseResistor(argv[i], resistance, prefix, eSeriesName))
        {
            std::cout << "Invalid input" << std::endl;
            return 2;
        }

        Prefix::Apply(prefix, resistance);

        eSeries = eSeriesName.empty() ? eSeriesDefault : NumberSeries::Find(eSeriesName);
        if(eSeries == nullptr)
        {
            std::cout << "Invalid E series \'" << eSeriesName << "\'" << std::endl;
            return 3;
        }

        // Create a new resistor and put it in the vector
        resistors.push_back(Resistor(resistance, &(*eSeries)));
    }

    /*for(size_t i = 0U; i < resistors.size(); i++)
    {
        printf("Resistor[%zu]: Resistance=%lf, Tolerance=%lf\n", i, resistors[i].GetResistance(), resistors[i].GetTolerance());
    }*/

    double res = Resistor::CombinedResistance(resistors, cct);
    //double min = Resistor::CombinedMinResistance(resistors, cct);
    //double max = Resistor::CombinedMaxResistance(resistors, cct);
    //std::cout << "Total resistance: " << res << std::endl;
    //std::cout << "Total min. resistance: " << min << std::endl;
    //std::cout << "Total max. resistance: " << max << std::endl;
    //std::cout << "Tolerance: " << eSeries->GetTolerance() << std::endl;

    //double baseResistance = eSeries->Find(res);
    //std::cout << "Value to search a standard E-number for: " << NumberSeries::Standardize(res) << std::endl;
    //std::cout << "Standard E-number found: " << baseResistance << std::endl;

    int exponent = Prefix::CalcExponent(res);
    Resistor substitute(res, eSeriesDefault);
    //std::cout << "Exponent: " << exponent << std::endl;

    int mod = knutmod(exponent, 3);
    if(mod == 1) exponent--;
    else if(mod == 2) exponent++;

    //std::cout << "Exponent: " << exponent << std::endl;

    std::string symbol = Prefix::GetSymbol(exponent);
    std::cout << "Total resistance: " << res / Prefix::GetMultiplier(symbol) << symbol << std::endl;
    std::cout << "Substitute resistor: " << substitute.GetResistance(symbol) << symbol << std::endl;
    std::cout << "Color code: " << ColorString(substitute, 3) << std::endl;

    return 0;
}
