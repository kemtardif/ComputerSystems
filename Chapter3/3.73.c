#include <stdio.h>
typedef enum {NEG, ZERO, POS, OTHER} range_t;

range_t find_range(float x);

int main()
{
    float value[] = {-2.0, -1.0, 0.0, 1.0, 2.0};

    int i;
    for(i = 0; i < 5; i++)
    {
        range_t result = find_range(value[i]);

        printf("Value %f has range : %x \n" , value[i], result);
    }
}


range_t find_range(float x)
{
    asm(
        "vxorps %xmm1, %xmm1, %xmm1 #Set xmm1 to zero /n/t"
        "vucomiss $xmm1, %xmm0  #Set condition flags \n\t"
        "jp .L8 #NaN \n\t"
        "ja .L6 #Greater than zero \n\t"
        "je .L7 #Zero \n\t"
        "movl $0, %eax \n\t"
        "jmp .End \n\t"
        ".L8: \n\t"
        "movl $3, %eax \n\t"
        "jmp .End \n\t"
        ".L6: \n\t"
        "movl $2, %eax \n\t"
        "jmp .End \n\t"
        ".L7: \n\t"
        "movl $1, %eax \n\t"
        ".End : \n\t"
    );
}