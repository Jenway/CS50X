#include <stdio.h>
#include "../../../lib/cs50.h"
#define MAX 20

int main(void)
{
    // char name[MAX] = "hello";
    // scanf("%s" , &name);

    string name = get_string("What's your name? : ");
    printf("hello, %s !\n", name);

    int num = get_int("type in a number: ");
    printf("hello,%d\n", num);

    char c = get_char("type in a char: ");
    printf("you typed in %c\n", c);

    double d = get_double("type in a double: ");
    printf("you typed in %lf\n", d);

    float f = get_float("type in a float: ");
    printf("you typed in %f\n", f);

    long l = get_long("type in a long: ");
    printf("you typed in %ld\n", l);

    long long ll = get_long_long("type in a long long: ");
    printf("you typed in %lld\n", ll);

    char c1 = 0x65;
    printf("%d = %c\n", c1, c1 + 6);
    printf("You defined MAX as %d\n", MAX);
    printf("Bell ~ \007\n");
}
// ??