#include <stdio.h>
#include <string.h>
#include <ctype.h>
// #include <cs50.c>

int get_value(char *input,int value);

int const POINTERS[]={1,3,3,2,1,4,2,4,1,8,5,1,3,1,1,3,10,2,1,1,1,1,4,4,8,4,10};

int main(void){
    char input_1[10],input_2[10];
    int value_1,value_2,len;
    // string word1 = get_string((void*)".k",word1);
    // void* 是啥玩意？
    // printf("%s",word1);
    printf("Player 1:");
    gets(input_1); 
    // printf("input_1:%s\n",input_1);
    value_1 = get_value(input_1,value_1);
    // printf("value_1:%d\n",value_1);

    printf("Player 2:");
    gets(input_2);
    // printf("input_2:%s\n",input_2);
    value_2 = get_value(input_2,value_2);
    // printf("value_2:%d\n",value_2);

    if (value_1 > value_2)
    {
        printf("Player 1 wins!");
    }
    else if (value_1 < value_2)
    {
        printf("Player 2 wins!");
    }
    else
    {
        printf("Tie!");
    }
    
    
    
}

int get_value(char *input,int value){
    value = 0;
    for (int i = 0; i < strlen(input); i++)
    {   
        if (isupper(input[i]))
        {       
            value += ("%d",POINTERS[input[i] - 'A']);
        }
        else if (islower(input[i]))
        {
            value += ("%d",POINTERS[input[i] - 'a']);
        }
    }
    return value;
}