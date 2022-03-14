/*
 * mm-naive.c - The fastest, least memory-efficient malloc package.
 * 
 * In this naive approach, a block is allocated by simply incrementing
 * the brk pointer.  A block is pure payload. There are no headers or
 * footers.  Blocks are never coalesced or reused. Realloc is
 * implemented directly using mm_malloc and mm_free.
 *
 * NOTE TO STUDENTS: Replace this header comment with your own header
 * comment that gives a high level description of your solution.
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>

#include "mm.h"
#include "memlib.h"

/*********************************************************
 * NOTE TO STUDENTS: Before you do anything else, please
 * provide your team information in the following struct.
 ********************************************************/
team_t team = {
    /* Team name */
    "ateam",
    /* First member's full name */
    "Harry Bovik",
    /* First member's email address */
    "bovik@cs.cmu.edu",
    /* Second member's full name (leave blank if none) */
    "",
    /* Second member's email address (leave blank if none) */
    ""
};

/*Constants*/
#define ALIGNMENT 8
#define WORD 4
#define DWORD (WORD * 2)
#define CHUNK (1 << 8)

/* rounds up to the nearest multiple of DWORD */
#define ALIGN(size) (((size) + (DWORD-1)) & ~0x7)
#define SIZE_T_SIZE (ALIGN(sizeof(size_t)))

/*Global variables*/
static void *FREELIST_p;

/*Helpers*/

#define INSERT(p, val) (*(unsigned int *)(p) = val)
#define VALUEOF(p) (*(unsigned int *)(p))

#define SIZEOF(p) (VALUEOF((char *)p - WORD) & ~0x7)
#define ISALLOC(p) (VALUEOF((char *)p - WORD) & 0x1)

#define HEADER(p) ((char *)p - WORD)
#define FOOTER(p) ((char *)p + SIZEOF(p) - DWORD)

#define PREDD(p) (*(void **)p)
#define SUCC(p) (*(void **)((char *)p + WORD))

#define SETPREDD(p, np) (PREDD(p) = np)
#define SETSUCC(p, np) (SUCC(p) = np)

#define NEXTBLK(p) ((char *)p + SIZEOF(p))
#define PREVBLK(p) ((char *)p - SIZEOF((char *)p - WORD))

#define BOUND(size, bit) (size | bit)
#define MAX(x, y) x > y ? x : y

void heap_checker()
{
    printf("------------------------------------------ \n");
    if(!FREELIST_p)
    {
        printf("Free list is empty /n");
    } else 
    {
        void *end = FREELIST_p;
        while(end)
        {
            printf("***************************** \n");
            printf("FREE ADDRESS : %p \n", end);
            printf("IS ALLOC : %i \n", ISALLOC(end));
            printf("SIZE : %i \n", SIZEOF(end));
            if(PREDD(end))
            {
                printf("PREDECESSOR : %p \n", PREDD(end));
            } else 
            {
                printf("NO PREDECESSOR \n");
            }
            if(SUCC(end))
            {
                printf("SUCCESSOR : %p \n", SUCC(end));
            } else 
            {
                printf("NO SUCCESSOR \n");
            }
            if((size_t)end%8 != 0)
            {
                printf("NOT ALIGNED \n");
            }
            printf("***************************** \n");       
            end = SUCC(end);  
        }
    }
}

void *add_to_list(void *ptr)
{
    SETPREDD(ptr, NULL);
    SETSUCC(ptr, FREELIST_p);

    if(FREELIST_p)
        SETPREDD(FREELIST_p, ptr);   
    FREELIST_p = ptr;
    return ptr;
}

void remove_from_list(void *ptr)
{
    void *predecessor = PREDD(ptr);
    void *successor = SUCC(ptr);
    if(successor)
        SETPREDD(successor, predecessor);
    if(predecessor) 
        SETSUCC(predecessor, successor);
    else   
        FREELIST_p = successor; 

    return;
}


static void *coalesce(void * bp)
{
    size_t prev = ISALLOC(PREVBLK(bp));
    size_t next = ISALLOC(NEXTBLK(bp));
    size_t size = SIZEOF(bp);
    void * to_return;

    if(prev && next)
    {
        to_return =  bp;
    } 
    else if (!prev && next)
    {
        size += SIZEOF(PREVBLK(bp));
        remove_from_list(PREVBLK(bp));

        INSERT(HEADER(PREVBLK(bp)), BOUND(size, 0));
        INSERT(FOOTER(PREVBLK(bp)), BOUND(size, 0));
        to_return = PREVBLK(bp);      
    } 
    else if (prev && !next)
    {
        size += SIZEOF(NEXTBLK(bp));
        remove_from_list(NEXTBLK(bp));
        
        INSERT(HEADER(bp), BOUND(size, 0)); 
        INSERT(FOOTER(bp), BOUND(size, 0));
        to_return = bp;
    } 
    else 
    {
        size += SIZEOF(NEXTBLK(bp)) + 
                SIZEOF(PREVBLK(bp));

        remove_from_list(PREVBLK(bp));
        remove_from_list(NEXTBLK(bp));

        INSERT(HEADER(PREVBLK(bp)), BOUND(size, 0));
        INSERT(FOOTER(PREVBLK(bp)), BOUND(size, 0));
        to_return = PREVBLK(bp);
    }
    return to_return;
}


static void *extend_heap(size_t words)
{
    char *bp;
    size_t size;

    size = (words % 2) ? (words + 1) * WORD : words * WORD;
    if((long)(bp = mem_sbrk(size)) == -1)
        return NULL;

    INSERT(HEADER(bp), BOUND(size, 0));
    INSERT(FOOTER(bp), BOUND(size, 0));
    INSERT(HEADER(NEXTBLK(bp)), BOUND(0, 1));

    return add_to_list(coalesce(bp));
}
int mm_init(void)
{
    char *init;

    if((long)(init = mem_sbrk(2 * DWORD)) == -1)
        return -1;

    INSERT(init, 0);
    INSERT(init + (1*WORD), BOUND(DWORD, 1));
    INSERT(init + (2*WORD), BOUND(DWORD, 1));
    INSERT(init + (3*WORD), BOUND(0, 1));

    FREELIST_p = NULL;
    
    if(extend_heap(CHUNK/WORD) == NULL)
        return -1;
    return 0;
}

void *find_fit(size_t size)
{
    void *end = FREELIST_p;

    while(end)
    {
        if(size <= SIZEOF(end))
            return end;
        end = SUCC(end);
    }
    return NULL;
}

void place(void *ptr, size_t size)
{
    size_t difference;

    remove_from_list(ptr);
    if((difference = (SIZEOF(ptr) - size)) <= DWORD) 
    {
        INSERT(HEADER(ptr), BOUND(SIZEOF(ptr), 1));
        INSERT(FOOTER(ptr), BOUND(SIZEOF(ptr), 1));
    } 
    else
    {
        INSERT(HEADER(ptr), BOUND(size, 1));
        INSERT(FOOTER(ptr), BOUND(size, 1));

        INSERT(HEADER(NEXTBLK(ptr)), BOUND(difference, 0));
        INSERT(FOOTER(NEXTBLK(ptr)), BOUND(difference, 0));
        add_to_list(coalesce(NEXTBLK(ptr)));
    }
}

/* 
 * mm_malloc - Allocate a block by incrementing the brk pointer.
 *     Always allocate a block whose size is a multiple of the alignment.
 */
void *mm_malloc(size_t size)
{  
    size_t asize, extendsize;
    char *ptr;

    if(size == 0)
        return NULL;

    if(size <= ALIGNMENT)
        asize = 2 * ALIGNMENT;
    else
        asize = ALIGNMENT + ALIGN(size);

    if ((ptr = find_fit(asize)) != NULL) 
    {
        place(ptr, asize);
        return ptr;
    }
    extendsize = MAX(asize, CHUNK);
    if((ptr = extend_heap(extendsize/WORD)) == NULL)
        return NULL;
    place(ptr, asize);
    return ptr;
}

/*
 * mm_free .
 */
void mm_free(void *ptr)
{
    if(!ptr)
        return;

    size_t size = SIZEOF(ptr);

    INSERT(HEADER(ptr), BOUND(size, 0));
    INSERT(FOOTER(ptr), BOUND(size, 0));
    add_to_list(coalesce(ptr));
}

/*
 * mm_realloc - Implemented simply in terms of mm_malloc and mm_free
 */
void *mm_realloc(void *ptr, size_t size)
{
    printf("Hey, you are in realloc! /n");
    void *oldptr = ptr;
    void *newptr;
    size_t copySize;
    
    newptr = mm_malloc(size);
    if (newptr == NULL)
      return NULL;
    copySize = *(size_t *)((char *)oldptr - SIZE_T_SIZE);
    if (size < copySize)
      copySize = size;
    memcpy(newptr, oldptr, copySize);
    mm_free(oldptr);
    return newptr;
}














