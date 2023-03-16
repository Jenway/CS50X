#include "..\..\..\lib\cs50.h"
// #include <cs50.h>
#include <stdio.h>
#include <stdbool.h>

#include <stdlib.h>

string judge(const int answer, const int length);
int main(void)
{
    // printf("%lld\n",sizeof(long long));
    long long num = get_long_long("Number: ");
    int sum = 0, temp = 0, length = 0, ans = 0;
    bool isEvenPlace = false;

    for (size_t i = 0; num != 0; i++)
    {

        temp = isEvenPlace ? (num % 10) * 2 : num % 10;
        sum += temp >= 10 ? temp / 10 + temp % 10 : temp;
        isEvenPlace = !isEvenPlace;
        num /= 10;
        if (num >= 10 && num < 100)
        {
            ans = num;
        }

        length++;
    }
    // printf("ans:%d,len:%d\n", sum, length);
    printf("%s\n", sum % 10 == 0 ? judge(ans, length) : "INVALID");
    return 0;
}

string judge(const int answer, const int length)
{
    if ((answer == 34 || answer == 37) && length == 15)
    {
        return "AMEX";
    }
    else if (answer >= 51 && answer <= 55 && length == 16)
    {
        return "MASTERCARD";
    }
    else if (answer >= 40 && answer <= 49 && (length == 13 || length == 16))
    {
        return "VISA";
    }
    else
    {
        return "INVALID";
    }
}