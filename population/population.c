#include <cs50.h>
#include <stdio.h>

int main(void)
{
    float start_size;
    float end_size;
    float comp;
    int years = 0;

    // TODO: Prompt for start size
    do
    {
        start_size = get_int("Start size: ");
    }
    while (start_size < 9);

    // TODO: Prompt for end size
    do
    {
        end_size = get_int("End size: ");
    }
    while (end_size < start_size);

    // TODO: Calculate number of years until we reach threshold
    /**
     * 1 year : n llamas --> (13/12)n llamas
     * 2 years : n llamas --> (13/12)x(13/12)n llamas
     * 3 years : n llamas --> (13/12)x(13/12)x(13/12)n llamas
     * ....
     */
    comp = (13 * start_size / 12);
    while (comp <= (float)end_size)
    {
        years++;
        comp = (13 * comp / 12);
    }


    // TODO: Print number of years
    printf("Years: %i\n", years);
}