/*
1 sum_col:
2   leaq 1(,%rdi,4), %r8 // 1 + 4*n in %r8
3   leaq (%rdi,%rdi,2), // %rax // 3*n in %rax
4   movq %rax, %rdi     // 3*n in %rdi
5   testq %rax, %rax  //
6   jle .L4           // Check if n is 0 or negative
7   salq $3, %r8     // 8*(1+4*n) in %r8
8   leaq (%rsi,%rdx,8), %rcx // A + 8*j in %rcx
9   movl $0, %eax   //Set result = 0
10  movl $0, %edx   //Set i = 0
11 .L3:
12  addq (%rcx), %rax  // result += A[0][j]
13  addq $1, %rdx     // i++
14  addq %r8, %rcx    // Add 8*(1 + 4*n) to A + 8*j
15  cmpq %rdi, %rdx  // compare i and 3*n
16   jne .L3
17  rep; ret
18 .L4:
19  movl $0, %eax
20  ret


From line 4 and 15, we have NR(n) = 3*n, while from eq &A = A + 8*(NC(n)*i + j)
and line 14, we have NC(n) = 1 + 4*n

*/