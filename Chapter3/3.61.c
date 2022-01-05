/*
Conditional data transfert can be done using a simple if/else statement :
*/

long cread(long *xp) 
{
    return (!xp ? 0 : *xp);
}