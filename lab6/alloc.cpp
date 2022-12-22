#ifndef __MMU__H__
#define __MMU__H__
#define SIZE 20
#include <vector>
#include<iostream>
#include <time.h>
#include <bits/stdc++.h>

typedef short byte_t;

typedef int address_t;

// structure of a hole : an address and a size
typedef struct hole
{
    address_t adr;
    int sz;
    int frag=0;
} hole_t;

// structure of a memory : a size and a vector of holes
typedef struct
{
    byte_t mem[390];
    std::vector<hole_t> root;
    
} mem_t;

// dynamically allocates a mem_t structure and initializes its content
mem_t initMem()
{
    mem_t mem;

    std::vector<hole_t> root{{0,100},{100,50},{150,10},{160,20},{180,200},{280,110}};

    // we create a the first hole at address 0 and with size of all the memory
    // hole_t firstHole;
    // firstHole.adr = 0;
    // firstHole.sz = 10;

    

    // // we put it into the vector of holes
    // root.push_back(firstHole);

    // srand(time(NULL));

    // for (int i=1;i<SIZE;i++)
    // {
    //     hole_t hole;
    //     hole.adr=root[i-1].adr + root[i-1].sz;
    //     hole.sz=rand() % 200 + 1;  
    //     root.push_back(hole);
    // }
    
    std::cout << "adr" << "\t size\n" ;
    for(auto element : root )
{
 
 
 std::cout << element.adr << "\t" << element.sz << "\n";
}



    // we put the vector into the memory
    mem.root = root;

    return mem;
}

// allocates space in bytes (byte_t) using First-Fit, Best-Fit or Worst-Fit
address_t myAllocFirstFit(mem_t *mp, int sz)
{
    //First-Fit
    for (int i = 0; i < mp->root.size(); i++)
    {
        
        if (sz < mp->root[i].sz && mp->root[i].frag != 1)
        {
            mp->root[i].sz -= sz;	// decrease the size of the hole
            int adr=mp->root[i].adr;
            mp->root[i].adr += sz;	// increase the address of the hole
            mp->root[i].frag=1;
            return adr;	// return the address of the alloc
        }
        // if the hole is exactly the size of the alloc, we remove the hole
        else if(sz == mp->root[i].sz)
        {
            address_t ad = mp->root[i].adr - sz;	// put in a variable the address of the alloc

            mp->root.erase(mp->root.begin() + i); // delete the hole

            return ad; // return the address of the alloc
        }
    }

    std::cout << "No more available space in the memory\n";
    return -1;	// return -1 if the alloc is not possible
};

address_t myAllocWorstFit(mem_t *mp, int sz){
 //Worst-Fit
    int j;
    int max=0;
    for (int i = 0; i < mp->root.size(); i++)
    {
        
        if (max<=mp->root[i].sz && mp->root[i].frag != 1)
            {
                max=mp->root[i].sz;
            
            j=i;}

    }
        
        if(mp->root[j].sz>=sz)
        {
        //mp->root[j].sz -= sz;
    int adr=mp->root[j].adr;
            //mp->root[j].adr += sz;	// increase the address of the hole
            mp->root[j].frag=1;
            return adr;}
        
        else{  
    return -1;	// return -1 if the alloc is not possible
        }
};


// release memory that has already been allocated previously
void myFree(mem_t *mp, address_t p, int sz)
{   
    for (int i = 0; i < mp->root.size(); i++)
    {
        if(mp->root[i].adr==p)
        {
            mp->root[i].frag=0;

            std::cout << "addresse " << mp->root[i].adr << " size " << mp->root[i].sz << "\n";

        }
    }

};

// assign a value to a byte
void myWrite(mem_t *mp, address_t p, byte_t val)
{
    mp->mem[p]=val;
};

// read memory from a byte
byte_t myRead(mem_t *mp, address_t p)
{
    std::cout << "the value of the byte " <<p<< " is "<<mp->mem[p]<<"\n";
    return mp->mem[p];
};

#endif

int main()
{
    // initialization of the memory
    mem_t tempMem = initMem();
    mem_t *mem = &tempMem;	// we put it in a pointer so that we can modifiy it in the functions

    // allocation of 3 addresses
    address_t adr1 = myAllocWorstFit(mem, 5);	// new address with size of 5 in the memory
    address_t adr2 = myAllocWorstFit(mem, 20);	// new address with size of 10 in the memory
    address_t adr3 = myAllocWorstFit(mem, 100); // new address with size of 100 in the memory
    std::cout << "the new address with size 5 is " << adr1 << "\n";
    std::cout << "the new address with size 20 is " << adr2 << "\n";
    std::cout << "the new address with size 100 is " << adr3 << "\n";

    // free of 2 addresses
   myFree(mem, adr2, 20);	// free address 2 with size of 10
   myFree(mem, adr1, 5);	// free address 1 with size of 5

    myWrite(mem, adr3, 543);    // write on the 1st byte
    myWrite(mem, adr3 + 9, 34); // write on the 10th byte
    byte_t val1 = myRead(mem, adr3);	
    byte_t val2 = myRead(mem, adr3 + 9);
}