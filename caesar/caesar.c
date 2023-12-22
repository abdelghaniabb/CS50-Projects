#include <cs50.h>
#include <stdio.h>

int _isdigit(int c);
int _atoi(char *s);
int _isupper(int c);
int _islower(int c);

int main(int argc, string argv[])
{
    int i;
    int k, c, p;
    char *s = argv[1];
    string text;
    string ascii_lowercase = "abcdefghijklmnopqrstuvwxyz";
    string ascii_uppercase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    // Make sure program was run with just one command-line argument
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return (0);
    }
    // Make sure every character in argv[1] is a digit
    i = 0;
    while (argv[1][i] != '\0')
    {
        if (_isdigit(argv[1][0]) == 0)
        {
            printf("Usage: ./caesar key\n");
            return (0);
        }
        i++;
    }
    // Convert argv[1] from a `string` to an `int`
    k = _atoi(s);
    // Prompt user for plaintext
    text = get_string("plaintext:  ");
    // For each character in the plaintext:
    // Rotate the character if it's a letter
    printf("ciphertext: ");
    i = 0;
    while (text[i] != '\0')
    {
        if (_isupper(text[i]) == 1)
        {
            p = text[i] - 'A';
            c = (p + k) % 26;
            printf("%c", ascii_uppercase[c]);
        }
        else if (_islower(text[i]) == 1)
        {
            p = text[i] - 'a';
            c = (p + k) % 26;
            printf("%c", ascii_lowercase[c]);
        }
        else
        {
            printf("%c", text[i]);
        }
        i++;
    }
    printf("\n");
    return (0);
}

int _isdigit(int c)
{
    if (c >= '0' && c <= '9')
    {
        return (1);
    }
    return (0);
}

int _atoi(char *s)
{
    int result = 0;

    while (*s != '\0')
    {
        result = result * 10 + (*s - '0');
        s++;
    }

    return (result);
}

int _isupper(int c)
{
    if (c >= 'A' && c <= 'Z')
    {
        return (1);
    }
    return (0);
}

int _islower(int c)
{
    if (c >= 'a' && c <= 'z')
    {
        return (1);
    }
    return (0);
}