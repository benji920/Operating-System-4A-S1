#include <stdbool.h>

#define __MMU__H__
#define __MMU__H__
#define SIZE 65536

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

typedef short byte_t;

typedef int address_t;

typedef struct {
byte_t mem[SIZE];
int root[SIZE];
} mem_t;

mem_t *initMem(){
    
    mem_t mem;
    mem_t *point;

for (int i=0;i<SIZE;i++)
{
    mem.root[i]=0;
}

point=&mem;
return *point;

}

int main(){

mem_t *mem;
mem=initMem();

for (int i=0;i<SIZE;i++)
{
    printf("%d\n",mem->root[i]);
}

}