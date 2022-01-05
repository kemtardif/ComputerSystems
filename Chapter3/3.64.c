/*
A.The formulate readily extend to 3-dimensional arrays by noting that the additionnal
dimension has the effect of dividind each cell by T, hence &A[i][j][k] = xA + L*(S*T*i + T*j + k)

B. Annotating the AL code : 

store_ele:
    leaq (%rsi,%rsi,2), %rax // 3*j in %rax
    leaq (%rsi,%rax,4), %rax // 13*j in %rax
    movq %rdi, %rsi // i in %rsi
    salq $6, %rsi  // i << 6 = 64*i in %rsi
    addq %rsi, %rdi // 65*i in %rdi
    addq %rax, %rdi // 65*i + 13*j in %rdi
    addq %rdi, %rdx // 65*i + 13*j + k in %rdx
    movq A(,%rdx,8), %rax //A + 8*(65*i + 13*j + k) in %rax
    movq %rax, (%rcx) // A + 8*(65*i + 13*j + k) in memory (%rcx)
    movl $3640, %eax //return 3640
    ret

It immediately follow that T = 13, S = 5, hence for the return value R*S*T*8 = 3640,
we have R=7
*/