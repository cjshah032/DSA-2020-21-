//when ./test hello world is run, value of argc = 3     //exercise 1a
#include<stdio.h>
#include<stdbool.h>

bool isInt(char s[])
{
    int n = sizeof(s)/sizeof(s[0]);
    for(int i=0; i<n; i++)
    {
        if(!(s[i] >= '0' && s[i] <= '9'))
            return false;
    }

    return true;
}

int main(int argc, char* argv[])
{
    for(int i=0; i<argc; i++)
    {
        if(isInt(argv[i]))  //exercise 1c
        {
            int temp = atoi(argv[i]);
            printf("%d", temp);
            continue;
        }

        printf("%s ", argv[i]);     //exercise 1b
    }
        
    return 0;
}