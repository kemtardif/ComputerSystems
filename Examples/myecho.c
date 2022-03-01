#include <stdio.h>

int main(int argc, char *argv[])
{
    int i = 0;
    int passed = 0;

    printf("START \n");
    while(passed != 2)
    {
        if(argv[i] == NULL)
        {
            if(passed == 0)
            {
                printf("End of arguments \n");
                passed = 1;
            } else if (passed == 1)
            {
                 printf("End of Envrionment variables \n");
                 passed = 2;
            } else 
            {
                printf("argv[i] is NULL on iteration : %i \n", i);
            }

        } else 
        {
            printf("%s \n", argv[i]);
        }
        i++;
    }
    printf("END \n");
}