#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include "LogicGates.hpp"

int main(/*int argc, char *argv[]*/)
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
    return 0;
}
