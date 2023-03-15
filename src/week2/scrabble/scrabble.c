#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "../../../lib/cs50.h"

const int SCORES[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 2, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int get_value(string input);

int main(void)
{
    string input_1 = get_string("Player 1: ");
    string input_2 = get_string("Player 2: ");
    // printf("%d %d", get_value(input_1), get_value(input_2));
    int value_1 = get_value(input_1), value_2 = get_value(input_2);
    if (value_1 > value_2)
    {
        printf("Player 1 wins!\n");
    }
    else if (value_1 < value_2)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }

    return 0;
}

int get_value(string input)
{
    int score = 0;
    for (size_t i = 0; i < strlen(input); i++)
    {
        if (input[i] <= 'z' && input[i] >= 'A')
        {
            score += isupper(input[i]) ? SCORES[input[i] - 'A'] : SCORES[input[i] - 'a'];
        }
    }
    return score;
}