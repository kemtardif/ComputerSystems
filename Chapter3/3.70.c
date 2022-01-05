/*
A. e1.p and e2.x have offset 0 while e1.y and e2.next have offset 8

B. Total bytes of a union is the max size of its elements, which is 16 bytes

C.

void proc (union ele *up) 
{
    up->e2.x = *((up->e2.next)->e1.p) - ((up->e2.next)->e1.y);
}

*/