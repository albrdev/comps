#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <regex>
#include "Resistor.hpp"
#include "ESeries.hpp"
#include "Prefix.hpp"
#include "xmath.h"
#include "optargs.h"

enum RoundingMode
{
    RM_NONE = 0,
    RM_NEAREST = 1,
    RM_FROM_ZERO = 2,
    RM_TO_ZERO = 3,
    RM_UP = 4,
    RM_DOWN = 5
};

int roundExponent(const int exp, const RoundingMode mode)
{
    switch(mode)
    {
        case RM_NEAREST:
        {
            int mod = mod_floor(exp, 3);
            if(mod != 0)
            {
                return exp + (mod < (3 / 2.0) ? -mod : 3 - mod); // Set to nearest number divisible by 3
            }
            else
            {
                return 0;
            }
        }

        case RM_FROM_ZERO: { return (int)((exp > 0 ? ceil(exp / 3.0) : floor(exp / 3.0)) * 3); break; }
        case RM_TO_ZERO: { return exp / 3 * 3; }
        case RM_UP: { return (int)ceil(exp / 3.0) * 3; }
        case RM_DOWN: { return (int)floor(exp / 3.0) * 3; }
        default: { throw; }
    }
}

std::vector<Resistor> resistors;
std::string input;
CircuitConnectionType cct = CircuitConnectionType::CCT_INVALID;
const ESeries *eSeriesDefault;

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

static void printusage(void)
{
    fprintf(stderr, "Usage: comps_resistor -t s|p resistance[prefix][, tolerance|e-series]...\n");
}

static int parsearg(const char *const name, const char *const value)
{
    if(name == nullptr && value == nullptr)
        return -1;

    if(name == nullptr)
    {
        if(*value == '\0') return 0;

        double resistance;
        std::string prefix;
        std::string misc;
        const ESeries *eSeries;

        if(ParseInput(value, resistance, prefix, misc))
        {
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
            std::vector<std::string> colors = splitString(value, ' ');
            if(colors.size() < 3 || colors.size() > 6)
            {
                fprintf(stderr, "Invalid resistor input: \'%s\'\n", value);
                return 2;
            }

            resistors.push_back(Resistor(colors, eSeriesDefault));
        }
    }
    else if(strcmp(name, "t") == 0 || strcmp(name, "type") == 0)
    {
        if(value == nullptr)
        {
            fprintf(stderr, "Invalid circuit type: %s\n", name);
            return 1;
        }

        if(strcmp(value, "s") == 0 || strcmp(value, "serial") == 0)
        {
            cct = CircuitConnectionType::CCT_SERIAL;
        }
        else if(strcmp(value, "p") == 0 || strcmp(value, "parallel") == 0)
        {
            cct = CircuitConnectionType::CCT_PARALLEL;
        }
        else
        {
            fprintf(stderr, "Invalid circuit type: %s\n", value);
            return 1;
        }
    }
    else if(strcmp(name, "h") == 0 || strcmp(name, "help") == 0)
    {
        printusage();
        exit(EXIT_SUCCESS);
    }
    else
    {
        printf("Unknown option: %s\n", name);
        return 1;
    }

    return 0;
}

static void parseargs(char *const argv[], const int argc)
{
    if(argc < 2 + 1)
    {
        fprintf(stderr, "Insufficient arguments\n");
        exit(EXIT_FAILURE);
    }

    if(optargs_parse(argv, argc, parsearg) != 0)
    {
        fprintf(stderr, "Could not parse argument list\n");
        exit(EXIT_FAILURE);
    }

    if(cct == CircuitConnectionType::CCT_INVALID)
    {
        fprintf(stderr, "Invalid circuit type\n");
        exit(EXIT_FAILURE);
    }

    if(resistors.empty())
    {
        fprintf(stderr, "Insufficient arguments\n");
        exit(EXIT_FAILURE);
    }

    for(size_t i = 0U; i < resistors.size(); i++)
    {
        int e = Prefix::CalcExponent(resistors[i].GetResistance());
        e = roundExponent(e, resistors[i].GetResistance() < 1.0 ? RoundingMode::RM_FROM_ZERO : RoundingMode::RM_TO_ZERO);
        std::string symbol = Prefix::GetSymbol(e);
        printf("Added: %s\n", resistors[i].ToString(symbol).c_str());
    }

    putchar('\n');
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
    setp(2);

    if(setvbuf(stderr, NULL, _IONBF, 0U) != 0)
    {
        fprintf(stderr, "Could not set \'stderr\' unbuffered\n");
        fflush(stderr);
        return 1;
    }

    eSeriesDefault = ESeries::Find("E24");
    parseargs(argv, argc);

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
