#include <stdio.h>

int main(void) 
{
    int height;
    do
    {
        printf("Height:");
        scanf("%d", &height);
    }
    while (height < 1 || height > 8);
    printf("%d\n",height);
    for (int i = 0; i < height; i++)
    {
        for (int j = height - i ; j > 1; j--)
        {
            printf(" ");
        }
        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }
        printf("  ");
        for (int j = 0 ; j <= i; j++)
        {
            printf("#");
        }
        printf("\n");
        
    }
    
    return 0;
}


