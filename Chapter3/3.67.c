/*
A. 
 return Address
 ----------------
|                |   
|                |
|                |   
|        z       | <= %rsp + 80
|        x       | <= %rsp + 72
|        y       | <= %rsp + 64
|                |   
|                |
|       z        | <= %rsp + 24
|       &z       | <= %rsp + 16
|       y        | <= %rsp + 8
|       x        | <= %rsp

B. Looking at line 8 in eval, we see that %rdi is set to to %rsp + 64,
a pointer to the address of s.

C. Values are accessed by an offset i.e. x @ %rsp + 8, y @ %rsp + 16 and &z @ %rsp +24

D. Values are stored w.r.t. %rsp + 64 in %rdi i.e. %rdi, &rdi + 8 and % rdi + 16


F. The caller pass the address for the starting address of the structure, and the callee
set the values w.r.t to that address with appropriate offsets.

*/