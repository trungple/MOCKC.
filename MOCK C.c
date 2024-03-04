#include <stdio.h>
#include <stdlib.h>
#include<math.h>
typedef struct tLucky {
    char name[30];
    float LuckyRatio;
    int GuessedNum ;
}Lucky;

int SetRandomNumber() 
{
    return rand() % 1000;
}

void compar(int a, int b)
{
    for (int i = 4; i >0 ; i--)
    {
        int digitA = (a % ((int)pow(10, i))) / ((int)pow(10, i - 1));
        int digitB = (b % ((int)pow(10, i))) / ((int)pow(10, i - 1));

        if (digitA == digitB)
        {
            printf("%d", digitA);
        }
        else
        {
            printf("-");
        }
    }
}

int main()
{   
    char cOption;
    int count=0;
    int numPlayers=0;
    Lucky *new=(Lucky*)malloc(100*sizeof(Lucky));


    if(new==0)
    {
        printf("allocate fail");
        return 1; 
    }
    do{
    
        int num=SetRandomNumber();

        printf("input your name: ");
        scanf("%s",new->name);

        count ++;
        numPlayers++;
        do
        {
            printf("input your number: ");
            scanf("%d",&new->GuessedNum);

            getc(stdin);

            compar( new->GuessedNum, num);
        }while(new->GuessedNum!=num);
        

        printf("do you wanna continue:");
        scanf(" %c",&cOption);

        float luckyratio =1/count;

    }while(cOption=='y');

    free(new);
    
}