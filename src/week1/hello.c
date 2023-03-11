#include <stdio.h>
#define MAX 20 

int main(void){
    char name[MAX] = "hello";
    printf("%s??",name);
    // scanf("%s" , &name);
    printf("hello,%s\n", name);
    char c1 = 0x65;
    printf("%d = %c\n",c1,c1 + 6);
    printf("\007");
}
// ??