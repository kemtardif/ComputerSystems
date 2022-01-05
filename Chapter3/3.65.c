/*
.L6:
    movq (%rdx), %rcx // Get (%rdx) in %rcx (long t = A[i][j])
    movq (%rax), %rsi // 
    movq %rsi, (%rdx) // Set (%rdx) to (%rax) (A[i][j] = A[j][i])
    movq %rcx, (%rax) // Set (%rax) to %rac (A[j][i] = t)
    addq $8, %rdx // Add 8 to %rdx (A[i][j] => A[i][j + 1])
    addq $120, %rax //Add 120 to %rax (A[j + 1][i])
    cmpq %rdi, %rax // A[j + 1][i] - %rdi
    jne .L6

A. Register %rdx holds a pointer to A[i][j]
B. Register %rax holds a pointer to A[j][i]
C. 120/8 = 15, hence  = 15
*/