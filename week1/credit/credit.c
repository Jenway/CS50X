#include <stdio.h>
#define  MAX 18

void read_number();
void get_answer();
void judge();

int number;
int length = 0;
int answer = 0;
char *reply;

// 易错情况：错误
// 1、char a[10]; a[10]="hello";//一个字符怎么能容纳一个字符串？况且a[10]也是不存在的！

// 这个最常见错误：
// 2、char a[10]; a="hello";//这种情况容易出现，a虽然是指针，但是它已经指向在堆栈中分配的10个字符空间，现在这个情况a又指向数据区中的hello常量，这里的指针a出现混乱，不允许！会出现const char无法转换为 char类型

// 3 、补充一点 char *a; a="hello";//这种情况是正确的。因为定义时a还没有指向的空间，不存在指针指向混乱的情况。

int main(void){

    read_number();
    // scanf("%d", &number);

    printf("You typed in: %d\n",number);

    get_answer(number,length,answer);
    judge(); 

    printf("length: %d\n",length);
    printf("answer: %d\n",answer);
    printf("reply: %s\n", reply);

}

    // check length sth worthy noticed
    // 这个地方非常有趣，如果是"\0" 这里就会报错，提示comaprison between integer and pointer 
    // seems if "\0" it will be a pointer
    // while if '\0' it will be a integar
    // for (int i = 0; number[i] != '\0'; i++)
    // {
    //     printf("%d\n",number[length]);
    //     printf("loop\n");
    //     length++;
    // }


void read_number(){
    // limit the input here
    // !! bug !!
    printf("Number:");
    while (scanf("%d", &number) != 1)
    {
        while(getchar() != '\n' && getchar() != EOF);
        // 清理缓存区
        printf("Number:");        
    }
}
void get_answer(){
    int remainder = 0;
    int answer_tail,answer_subtail = 0;
    for (int num = number; num > 0; length ++)
    {
        remainder = num % 10;
        if (length % 2 == 0)
        {
            answer_tail += remainder;
        }
        else
        {
            answer_subtail += remainder;
        }
        
        // 从倒数第二位每隔一位相加
        
        num /= 10;

    }
    if (length % 2 == 0)
    {
        answer = answer_tail;
    }
    else
    {
        answer = answer_subtail;
    }
}  
void judge(){
    if ((answer == 34 || answer == 37) && length == 15)
    {
        reply = "AMEX";
    } 
    else if (answer >= 51 && answer <= 55 && length == 16)
    {
        reply = "MASTERCARD";
    } 
    else if (answer >= 40 && answer <= 49 && (length == 13 || length == 16))
    {
        reply = "VISA";
    }    
    else  
    {
        reply = "INVALID";
    }
}