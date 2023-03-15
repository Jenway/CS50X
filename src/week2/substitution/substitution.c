#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "../../../lib/cs50.h"

int main(int argc, char *argv[])
{
    string givenList = argv[1];

    if (argc < 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters!\n");
        return 1;
    }
    for (size_t i = 0; i < 26; i++)
    {
        if (!isalpha(givenList[i]))
        {

            printf("Key must contain 26 characters!\n");
            return 1;
        }
    }

    string plainText = get_string("plaintext:  ");

    for (size_t i = 0, temp = 0; i < strlen(plainText); i++)
    {
        temp = plainText[i];
        if (isalpha(temp))
        {
            if (isupper(temp))
            {
                plainText[i] = toupper(givenList[temp - 'A']);
            }
            else
            {
                plainText[i] = tolower(givenList[temp - 'a']);
            }
        }
    }
    printf("ciphertext: %s", plainText);

    return 0;
}
