#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int h;
    int i, j;

    do
    {
        h = get_int("Height: ");
    }
    while (h <= 0 || h > 8);

    //loop the lines
    for (i = 1; i <= h; i++)
    {
        //loop the chars in the line and put space
        for (j = 1; j < h - i + 1; j++)
        {
            putchar(' ');
        }
        //loop the chars in the line and put # in the end
        // put the number of # equal to the line number
        for (j = h - i + 1; j <= h; j++)
        {
            putchar('#');
        }
        // put the space
        putchar(' ');
        putchar(' ');
        // put the number of # equal to the line number
        for (j = h - i + 1; j <= h; j++)
        {
            putchar('#');
        }
        putchar('\n');
    }
}