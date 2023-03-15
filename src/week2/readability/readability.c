#include "../../../lib/cs50.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
// #include <stdbool.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    // get the target content
    string content = get_string("Text: ");
    float index = 5.88 * ((float)count_letters(content) / (float)count_words(content)) - 29.6 * ((float)count_sentences(content) / (float)count_words(content)) - 15.8;
    // printf("%d,%d,%d\n", count_letters(content), count_words(content), count_sentences(content));
    int ans = round(index);
    if (ans < 1)
    {
        printf("Before Grade 1");
    }
    else if (ans >= 16)
    {
        printf("Grade 16+");
    }
    else
    {
        printf("Grade %d", ans);
    }
}

int count_letters(string text)
{
    int letters_count = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (isalpha(text[i]) != 0)
        {
            letters_count++;
        }
    }
    return letters_count;
}

int count_words(string text)
{
    // if had cross over a space from alphabeta
    bool has_separated = false;
    int words_count = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] == ' ')
        {
            words_count++;
        }
    }
    words_count++;
    return words_count;
}

int count_sentences(string text)
{
    int sentences_count = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentences_count++;
        }
    }
    return sentences_count;
}