#include <stdio.h>
#include <stdlib.h>


void good_echo();

int main()
{
    good_echo();
}

void good_echo()
{
    char buf[255];

    char *result = fgets(buf, sizeof(buf), stdin);

    if(result == NULL)
    {
        printf("There was an error");
    } else
    {
        printf("This is your characters : %s", buf);
    }
}