#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <set>
#include <cmath>
#include <iomanip>
#include <memory>
#include <regex>
#include "Resistor.hpp"
#include "ESeries.hpp"
#include "Prefix.hpp"
#include "xmath.h"
#include "LogicGates.hpp"

#define arraycount(arr) (sizeof(arr) / sizeof(*arr))

bool ParseInput(const std::string &input, double &resistance, std::string &prefix, std::string &eSeries)
{
    std::regex regex(R"(^(-?[\d]+\.?[\d]*)([GMkmuKgU]?),?\s*([eE][\d]+|-?[\d]+\.?[\d]*%?)?$)");
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

enum RoundingMode
{
    RM_NONE = 0,
    RM_NEAREST = 1,
    RM_FROM_ZERO = 2,
    RM_TO_ZERO = 3,
    RM_UP = 4,
    RM_DOWN = 5
};

int roundExponent(const int value, const RoundingMode mode)
{
    switch(mode)
    {
        case RM_NEAREST:
        {
            int mod = mod_floor(value, 3);
            if(mod != 0)
            {
                return value + (mod < (3 / 2.0) ? -mod : 3 - mod); // Set to nearest number divisible by 3
                //if(mod == 1) exponent--;
                //else if(mod == 2) exponent++;
            }
            break;
        }

        case RM_FROM_ZERO:
        {
            return (int)((value > 0 ? ceil(value / 3.0) : floor(value / 3.0)) * 3);
            break;
        }

        case RM_TO_ZERO:
        {
            return value / 3 * 3;
            break;
        }

        case RM_UP:
        {
            return (int)ceil(value / 3.0) * 3;
            break;
        }

        case RM_DOWN:
        {
            return (int)floor(value / 3.0) * 3;
            break;
        }

        default:
            break;
    }

    return 0;
}

std::vector<std::string> splitString(const std::string &value, const char delimiter)
{
    //std::istringstream ss(value);
    //return std::vector<std::string>(std::istream_iterator<std::string>(ss), std::istream_iterator<std::string>());

    std::stringstream ss(value);
    std::string str;
    std::vector<std::string> result;
    while(std::getline(ss, str, delimiter))
    {
        result.push_back(str);
    }

    return result;
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
    printf("A B C D\n");
    for(int a = 0; a < 2; a++)
    {
        for(int b = 0; b < 2; b++)
        {
            for(int c = 0; c < 2; c++)
            {
                for(int d = 0; d < 2; d++)
                {
                    printf("%d %d %d %d", a, b, c, d);
                    printf(" = %d\n", (bool)AND(AND(NOT(OR(a, b)), OR(c, d)), NOT(c)));
                }
            }
        }
    }

    return 0;

    std::vector<Resistor> resistors;
    std::string input;
    CircuitConnectionType cct;

    setp(2);

    if(setvbuf(stderr, NULL, _IONBF, 0U) != 0)
    {
        fprintf(stderr, "Could not set \'stderr\' unbuffered\n");
        fflush(stderr);
        return 1;
    }

    if(argc < 3)
    {
        fprintf(stderr, "Usage: components -{s|p} resistance[prefix][, tolerance|e-series]...\n");
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
        fprintf(stderr, "Invalid circuit connection specified: \'%s\'\n", argv[1]);
        return 1;
    }

    const ESeries *eSeriesDefault = ESeries::Find("E24");
    const ESeries *eSeries;

    for(int i=2; i<argc; i++)
    {
        if(*argv[i] == '\0') continue;

        double resistance;
        std::string prefix;
        std::string misc;
        if(ParseInput(argv[i], resistance, prefix, misc))
        {
            if(prefix == "K")
                prefix = "k";
            else if(prefix == "g")
                prefix = "G";
            else if(prefix == "U")
                prefix = "u";

            Prefix::Apply(prefix, resistance);

            eSeries = misc.empty() ? eSeriesDefault : ESeries::Find(misc);
            if(eSeries != nullptr)
            {
                resistors.push_back(Resistor(resistance, eSeries));
            }
            else
            {
                char *end = nullptr;
                double tolerance = strtod(misc.c_str(), &end);
                if(*end != '\0')
                {
                    if(strcmp(end, "%") == 0)
                    {
                        tolerance = pctodec(tolerance);
                    }
                    else
                    {
                        fprintf(stderr, "Invalid E-series/tolerance: %s\n", misc.c_str());
                        return 3;
                    }
                }

                resistors.push_back(Resistor(resistance, tolerance));
            }
        }
        else
        {
            std::vector<std::string> colors = splitString(argv[i], ' ');
            if(colors.size() < 3 || colors.size() > 6)
            {
                fprintf(stderr, "Invalid resistor input: \'%s\'\n", argv[i]);
                return 2;
            }

            resistors.push_back(Resistor(colors, eSeriesDefault));
        }

        int e = Prefix::CalcExponent(resistors.back().GetResistance());
        e = roundExponent(e, resistors.back().GetResistance() < 1.0 ? RoundingMode::RM_FROM_ZERO : RoundingMode::RM_TO_ZERO);
        std::string symbol = Prefix::GetSymbol(e);
        printf("Added: %s\n", resistors.back().ToString(symbol).c_str());
    }

    putchar('\n');

    /*for(size_t i = 0U; i < resistors.size(); i++)
    {
        printf("Resistor[%zu]: Resistance=%lf, Tolerance=%lf\n", i, resistors[i].GetResistance(), resistors[i].GetTolerance());
    }*/

    double res = Resistor::CombinedResistance(resistors, cct);
    double min = Resistor::CombinedMinResistance(resistors, cct);
    double max = Resistor::CombinedMaxResistance(resistors, cct);

    //double baseResistance = eSeries->Find(res);
    //std::cout << "Value to search a standard E-number for: " << NumberSeries::Standardize(res) << std::endl;
    //std::cout << "Standard E-number found: " << baseResistance << std::endl;

    //Resistor total = Resistor::Combine(resistors, cct);
    Resistor substitute(res, 0.05, eSeriesDefault);
    //printf("Total tolerance: %lf\n", total.GetTolerance());

    int exp_total = Prefix::CalcExponent(res);
    exp_total = roundExponent(exp_total, substitute.GetResistance() < 1.0 ? RoundingMode::RM_FROM_ZERO : RoundingMode::RM_TO_ZERO);
    std::string symbol_total = Prefix::GetSymbol(exp_total);
    double multiplier_total = Prefix::GetMultiplier(symbol_total);
    printf("Total resistance:       %.2lf%s [%.2lf%s, %.2lf%s]\n", res / multiplier_total, symbol_total.c_str(), min / multiplier_total, symbol_total.c_str(), max / multiplier_total, symbol_total.c_str());
    //printf("Total resistance:       %.2lf%s [%.2lf%s, %.2lf%s]\n", total.GetResistance(symbol), symbol.c_str(), total.GetMinResistance(symbol), symbol.c_str(), total.GetMaxResistance(symbol), symbol.c_str());

    int exp_substitute = Prefix::CalcExponent(substitute.GetResistance());
    exp_substitute = roundExponent(exp_substitute, substitute.GetResistance() < 1.0 ? RoundingMode::RM_FROM_ZERO : RoundingMode::RM_TO_ZERO);
    std::string symbol_substitute = Prefix::GetSymbol(exp_substitute);
    printf("Substitute resistor:    %.2lf%s [%.2lf%s, %.2lf%s]\n", substitute.GetResistance(symbol_substitute), symbol_substitute.c_str(), substitute.GetMinResistance(symbol_substitute), symbol_substitute.c_str(), substitute.GetMaxResistance(symbol_substitute), symbol_substitute.c_str());

    printf("Color code:             %s\n", substitute.GetColorString(3).c_str());

    return 0;
}
