#include <cs50.h>
#include <stdio.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
int _isalpha(int c);


int main(void)
{
    int letters, words, sentences;
    float L = 0, S = 0, index;

    string text = get_string("Text: ");
    letters = count_letters(text);
    if (letters != 0)
    {
        words = count_words(text) + 1;
    }
    else
    {
        words = count_words(text);
    }
    sentences = count_sentences(text);



    if (words != 0)
    {
        L = letters / (float)words * 100;
        S = sentences / (float)words * 100;
        index = 0.0588 * L - 0.296 * S - 15.8;
    }
    else
    {
        index = 0;
    }

    
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", (int)(index + 0.5));
    }


}

int count_letters(string text)
{
    int i = 0;
    int s = 0;

    while (text[i] != '\0')
    {
        if (_isalpha(text[i]))
        {
            s++;
        }
        i++;
    }
    return (s);
}
int count_words(string text)
{
    int i = 0;
    int s = 0;

    while (text[i] != '\0')
    {
        if (text[i] == ' ')
        {
            s++;
        }
        i++;
    }
    return (s);
}
int count_sentences(string text)
{
    int i = 0;
    int s = 0;

    while (text[i] != '\0')
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            s++;
        }
        i++;
    }
    return (s);
}

int _isalpha(int c)
{
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
    {
        return (1);
    }
    return (0);
}


