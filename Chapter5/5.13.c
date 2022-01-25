/*

A. The final critical path is :

    %xmm0                       %rcx
        |                          |
        |             ____|LOAD|___|
        |            |             |
        |            |  __|LOAD|___|
        |            | |           | 
    |ADD|____|MUL|___|_|           |
        |                      |ADD|
        |                          |
    %xmm0                       %rcx


B.For double, we see the latency is 3.0 and 5.0 for addition and multiplcation.
  However, only the addition is on the critical path, since multiplication and 
  Loadings can be done in advance. Hence the lower bound on the CPE is 3.0.

C.In this case, the latencies are 1.0 and 3.0, so that the lower bound is 1.0

D.AS mentionned, loadings, multiplicatio nand updating can be done in advance for
out-of-order computer, so that all that matters is addition of both loaded values.
*/