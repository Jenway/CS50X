# include <stdio.h>
# include <stdlib.h>
# include <string.h>
#include <ctype.h>
# define MAX 26

int len(char *list);

int main (int argc,char *argv[MAX]){

    char plain[MAX];    
    char *std_list= argv[1];
    // printf("std_list = %s\n",std_list);
    // printf("i= %d\n",sizeof(std_list));   
    int exist[26] = {0};
    if (argc < 2)
    {
    printf("Usage: ./substitution key\n");
    return 1;
    }
    if (len(argv[1]) != 26)
    {
        printf("Key must contain 26 characters!\n");
        return 1;
    }
    for (int i = 0; i < 26; i++)
    {
        exist[toupper(std_list[i]) - 'A']++;
    }
    for (int i = 0; i < 26; i++)
    {
        if (exist[i] != 1)
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }
    }


    
    // while(argc)       
    // printf("%s\n",argv[--argc]);

    printf("Plaintext:");
    scanf("%s",&plain);


    for (int i = 0; i < len(plain); i++)
    {
        // printf(">???\n");
        int j = plain[i];
        // printf("j=%d\n",j);
        if ('a' <= j && j <= 'z')
        {
            // printf("stdlist_i = %c\n",std_list[j - 'a']);
            // printf("z=%d\n",'z');
            // printf("j=%d\n",j);
            plain[i] = tolower(std_list[j - 'a']);
        }
        else if ('A' <= j && j <= 'Z')
        {
            // printf("stdlist_I = %c\n",std_list[j - 'A']);
            plain[i] = toupper(std_list[j - 'A']);
        }
        else{continue;}
            
    }
    printf("Aftertext:%s\n",plain);
    
    return 0;
    
}

int len(char *list){
    int length = 0;
    while (list[length] != '\0')
    {
        // printf("char = %c\n",list[length] );
        // printf("l = %d\n",length);
        length ++;
    }
       
    // printf("l = %d\n",length);
    return length;
}