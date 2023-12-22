#include <cs50.h>
#include <stdio.h>

long get_input(void);
int checksum(long card_number);
int length(long card_number);
int starting_digits(long card_number);

//Luhn’s Algorithm
int main(void)
{
    //ask the user for the card number
    long card_number = get_input();

    //checksum
    int checksum = checksum(card_number);
    if (checksum == 0)
    {
        printf("INVALID\n");
        return (0);
    }

    // AMEX\n or MASTERCARD\n or VISA\n or INVALID\n
}

long get_input(void)
{
    long card_number;
    do
    {
        card_number = get_long("Number: ");
    }
    while(card_number < 0);
    return (card_number);
}

int checksum(long card_number)
{
    int i;
    long temp = card_number;

    while (temp >= 1)


}