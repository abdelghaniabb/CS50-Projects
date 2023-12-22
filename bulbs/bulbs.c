#include <cs50.h>
#include <stdio.h>
#include <string.h>

const int BITS_IN_BYTE = 8;

void print_bulb(int bit);
void bulbs(char *message);
int _strlen(char *s);

int main(void)
{
    int i = 0;
    char *binarr;
    string message = get_string("Message: ");
    bulbs(message);
    return (0);

}
void bulbs(char *message)
{
    int i, j, bit, len;
    char c;

    len = _strlen(message);
    for (i = 0; i < len; i++)
    {
        c = message[i];
        for (j = 7; j >= 0; j--)
        {
            bit = (c >> j) & 1;
            print_bulb(bit);
        }
        printf("\n");
    }
}
int _strlen(char *s)
{
    int len = 0;

    while (*s != '\0')
    {
        len++;
        s++;
    }
    return (len);
}

void print_bulb(int bit)
{
    if (bit == 0)
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (bit == 1)
    {
        // Light emoji
        printf("\U0001F7E1");
    }
}
