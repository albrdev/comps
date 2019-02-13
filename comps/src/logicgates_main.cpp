#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include "LogicGates.hpp"
#include "optargs.h"

std::vector<bool> vars;
bool tableopt;

static int parsearg(const char *const name, const char *const value)
{
    if(name == NULL && value == NULL)
        return -1;

    if(name == NULL)
    {
        int inp = 0;
        if(sscanf(value, "%d", &inp) != 1)
            return 2;

        vars.push_back(inp);
    }
    else if(strcmp(name, "t") == 0 || strcmp(name, "table") == 0)
    {
        tableopt = true;
    }
    else
    {
        printf("Unknown option: %s\n", name);
        return 1;
    }

    return 0;
}

void parseargs(char *const argv[], const int argc)
{
    if(argc < 1 + 1)
    {
        fprintf(stderr, "*** Error: Insufficient arguments\n");
        exit(EXIT_FAILURE);
    }

    if(optargs_parse(argv, argc, parsearg) != 0)
    {
        fprintf(stderr, "*** Error: Could not parse argument list\n");
        exit(EXIT_FAILURE);
    }

    if(!tableopt && vars.size() < 4U)
    {
        fprintf(stderr, "*** Error: Insufficient arguments\n");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[])
{
    parseargs(argv, argc);

    if(tableopt)
    {
        size_t n = 4;
        size_t size = 1 << n;
        bool *table = new bool[size];
        bool *tmp = new bool[n];

        printf("A B C D\n");
        for(size_t i = 0U; i < size; i++)
        {
            for(size_t j = 0U; j < n; j++)
            {
                tmp[j] = table[i] = (i >> j) & 1;
            }

            printf("%d %d %d %d = %d\n", tmp[0], tmp[1], tmp[2], tmp[3], (bool)AND(AND(NOR(tmp[0], tmp[1]), OR(tmp[2], tmp[3])), NOT(tmp[2])));
        }

        delete[] tmp;
        delete[] table;
    }
    else
    {
        printf("%d\n", (bool)AND(AND(NOR(vars[0], vars[1]), OR(vars[2], vars[3])), NOT(vars[2])));
    }

    return 0;
}
