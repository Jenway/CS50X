/*
 *
 * compile with this gcc .\population.c ..\..\..\lib\cs50.c -o population
 * or write a makefile if you like
 *
 */

#include "../../../lib/cs50.h"
#include <stdio.h>


int main(void)
{
    // TODO: Prompt for start size
    int start = 0, end = 0, num = 0;
    do
    {
        start = get_int("Start size: ");

    } while (start < 9);

    // TODO: Prompt for end size
    do
    {
        end = get_int("End size: ");
    } while (end < start);

    // TODO: Calculate number of years until we reach threshold
    if (end == start)
    {
        num = 0;
    }
    else
    {

        for (num = 0; end > start; num++)
        {
            start += start / 3 - start / 4;
        }
    }

    // TODO: Print number of years
    printf("Years: %d", num);
}
