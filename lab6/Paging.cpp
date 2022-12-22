#ifndef __MMU__H__
#define __MMU__H__
#define SIZE 65536
#define PAGE_SIZE 128
#include <vector>
#include <iostream>
#include <iostream>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

typedef short byte_t;

typedef int address_t;

// structure of a hole : an address and a size
typedef struct hole
{
    address_t adr;
    int sz;

} hole_t;

// structure of a memory : a size and a vector of holes
typedef struct mem
{
    int paging_table[SIZE/PAGE_SIZE];
    std::vector<hole_t> root;
} mem_t;

typedef struct ram
{
    byte_t RAM[SIZE];
    int frame[SIZE/PAGE_SIZE];

}ram_t;

ram_t ram;

// Initialize memory
mem_t initMem()
{
    mem_t mem;
    std::vector<hole_t> root;

    // we create a the first hole at address 0 and with size of all the memory
    hole_t Hole;
    Hole.adr = 0;
    Hole.sz = SIZE;
    root.push_back(Hole);

    mem.root = root;

    for(int i=0;i<(SIZE/PAGE_SIZE);i++)//we set every pages to -1
    {
        mem.paging_table[i]=-1;
    }

    return mem;
}

// allocates space in bytes (byte_t) using First-Fit
address_t FirstFitAlloc(mem_t *mp, int sz)
{
    for (int i = 0; i < mp->root.size(); i++)
    {
        // if the hole is big enough we decrease the size of the hole by the new size
        if (sz < mp->root[i].sz)
        {
            mp->root[i].sz -= sz;  // decrease the size of the hole
            mp->root[i].adr += sz; // increase the address of the hole

            return mp->root[i].adr - sz; // return the address of the alloc
        }
        // if the hole is exactly the size of the alloc, we remove the hole
        else if (sz == mp->root[i].sz)
        {
            address_t ad = mp->root[i].adr; // put in a variable the address of the alloc

            mp->root.erase(mp->root.begin() + i); // delete the hole

            return ad; // return the address of the alloc
        }
    }
    std::cout << "No more available space in the memory\n";
    return -1; // return -1 if the alloc is not possible
};

// allocates space in bytes (byte_t) using Worst-Fit
address_t WorstFitAlloc(mem_t *mp, int sz)
{
    int max = 0;
    int j = 0;

    // looks for the largest hole
    for (int i = 0; i < mp->root.size(); i++)
    {
        if (max <= mp->root[i].sz)
        {
            max = mp->root[i].sz;
            j = i;
        }
    }

    // if the hole is big enough we decrease the size of the hole 
    if (sz < mp->root[j].sz)
    {
        mp->root[j].sz -= sz;  // decrease the size of the hole
        mp->root[j].adr += sz; // increase the address of the hole

        return mp->root[j].adr - sz; // return the address of the alloc
    }
    // if the hole is exactly the size of the alloc, we remove the hole
    else if (sz == mp->root[j].sz)
    {
        address_t ad = mp->root[j].adr; // put in a variable the address of the alloc

        mp->root.erase(mp->root.begin() + j); // delete the hole

        return ad; // return the address of the alloc
    }

    
        std::cout << "No more available space in the memory\n";
        return -1;
    // return -1 if the alloc is not possible}
};

// allocates space in bytes (byte_t) using Best-Fit
address_t BestFitAlloc(mem_t *mp, int sz)
{
    int min = SIZE;
    int j = 0;

    //looks for the hole that has the closest size to the allocation size
    for (int i = 0; i < mp->root.size(); i++)
    {

        if (min >= mp->root[i].sz - sz && mp->root[i].sz - sz >= 0)
        {
            min = mp->root[i].sz - sz;
            j = i;
        }
    }

    // if the hole is big enough we decrease the size of the hole and increase the address
    if (sz < mp->root[j].sz)
    {
        mp->root[j].sz -= sz;  // decrease the size of the hole
        mp->root[j].adr += sz; // increase the address of the hole

        return mp->root[j].adr - sz; // return the address of the alloc
    }
    // if the hole is exactly the size of the alloc, we remove the hole
    else if (sz == mp->root[j].sz)
    {
        address_t ad = mp->root[j].adr; // put in a variable the address of the alloc

        mp->root.erase(mp->root.begin() + j); // delete the hole

        return ad; // return the address of the alloc
    }

        std::cout << "No more available space in the memory\n";
        return -1;
    // return -1 if the alloc is not possible}
};

address_t myAlloc(mem_t *mp, int sz)
{
    int logical_address=FirstFitAlloc(mp, sz); //use the previous lab allocation
    int first_page=logical_address/PAGE_SIZE;
    int last_page=(logical_address+sz)/PAGE_SIZE;
    int j=0;

    for(int i=first_page;i<=last_page;i++)//for each pages
    {
        if(mp->paging_table[i]<0)//if page isn't attributed
        {
            while(ram.frame[j]!=0 && j<(SIZE/128))//find the first frame which is free
            j++;

            if(j>=(SIZE/128))//no frame available
            {std::cout<< "No more frame availables";
            return -1;
            }
            ram.frame[j]=getpid(); //Bonus: we write process id in the ramif we run multiple process
            mp->paging_table[i]=j;// we write the address of the frame
            std::cout<< "page number "<<i<<" allocated to frame "<< j<< "\n";
        }
    }

    return logical_address;

}

// release memory that has already been allocated previously
void myContFree(mem_t *mp, address_t p, int sz)
{
    // boolean to know if there is a hole on side
    bool holeOnSides = false;

    // browse the holes
    for (int j = 0; j < mp->root.size(); j++)
    {
        // CASE 1 : There is a hole above and below
        if (mp->root[j].adr == p + sz && (j != 0 && (mp->root[j - 1].adr + mp->root[j - 1].sz) == p))
        {
           // std::cout << "Hole on both sides\n";
            // we increase size of the previous hole with the size the size of the previous hole + the size of the free alloc
            mp->root[j - 1].sz = mp->root[j - 1].sz + mp->root[j].sz + sz; // new size of the hole
            mp->root.erase(mp->root.begin() + j);                          // erase the next hole

            holeOnSides = true; 

            j = mp->root.size();
        }

        // CASE 2 : There is a hole above but not below
        else if (mp->root[j].adr == p + sz && (j == 0 || (mp->root[j - 1].adr + mp->root[j - 1].sz) != p))
        {
           // std::cout << "Hole on the right but not on the left\n";
            // we increase size of the previous hole with the size of the free alloc
            mp->root[j].sz = mp->root[j].sz + sz; // new size of the hole
            mp->root[j].adr -= sz;                // new address of the hole

            holeOnSides = true; // there is a hole on at least one side

            j = mp->root.size();
        }

        // CASE 3 : There is a hole below but not above
        else if (mp->root[j].adr != p + sz && (j != 0 && (mp->root[j - 1].adr + mp->root[j - 1].sz) == p))
        {
           // std::cout << "Hole on the left but not on the right\n";
            // we increase size of the previous hole with the size of the hole + the size of the free
            mp->root[j].sz = mp->root[j].sz + sz; // new size of the hole

            holeOnSides = true; // there is a hole on at least one side

            // we end the loop
            j = mp->root.size();
        }
    }

    // if there is no hole on the sides
    if (!holeOnSides)
    {
        // CASE 4 : There is an alloc on both sides
        for (int j = 0; j < mp->root.size(); j++)
        {
            if (mp->root[j].adr != p + sz && (j == 0 || (mp->root[j - 1].adr + mp->root[j - 1].sz) != p))
            {
               // std::cout << "Alloc on the left and on the right \n";
                // we create a new hole at the current index
                hole_t newHole;
                newHole.adr = p;
                newHole.sz = sz;
                mp->root.insert(mp->root.begin() + j, newHole);
                // we end the loop
                j = mp->root.size();
            }
        }
    }
};

void myFree(mem_t *mp, address_t p, int sz)
{   myContFree(mp,p,sz);
    int first_page=p/PAGE_SIZE;
    int last_page=(p+sz)/PAGE_SIZE;
    int j=0;
    for(int i=0; i< 10;i++)
 
    for(int i=first_page;i<=last_page;i++)//for each pages
    {
        
        if(mp->paging_table[i]!=(-1)){//if the page is allocated
            ram.frame[mp->paging_table[i]]=0;// we free the frames in the ram
           // we free the paging table
            std::cout << "page number "<<i<<" free \n";
            std::cout << "frame number "<<mp->paging_table[i]<<" free \n";
             mp->paging_table[i]=-1;
        }
    }

};

// // assign a value to a byte
void myWrite(mem_t *mp, address_t p, byte_t val)
{
    address_t address_frame=mp->paging_table[p/PAGE_SIZE]* PAGE_SIZE;// we multiply the page size by the frame size to get the frame address
    address_t offset= p%PAGE_SIZE;//we find the offset 
    ram.RAM[address_frame+offset]=val;// we write the value inside the write mempry space
};

// // read memory from a byte
byte_t myRead(mem_t *mp, address_t p)
{
       address_t address_frame = mp->paging_table[p/PAGE_SIZE]* PAGE_SIZE ;//we find the address fame in the paging table
    address_t offset = p%PAGE_SIZE;// we find the offset
    return ram.RAM[address_frame+offset];
};

#endif

int main()
{
    // initialization of the memory
    mem_t tempMem = initMem();
    mem_t *mem = &tempMem; 

    // allocation of 3 addresses
    address_t adr1 = myAlloc(mem, 5);   // new address with size of 5 in the memory
    address_t adr2 = myAlloc(mem, 10);  // new address with size of 10 in the memory
    address_t adr3 = myAlloc(mem, 200);

   myFree(mem, adr2, 10);
   myFree(mem, adr1, 5);

    myWrite(mem, adr3,543);
    myWrite(mem,adr3+9, 34 );

    int val1=myRead(mem, adr3);
    int val2= myRead(mem, adr3+9);
        std::cout << "\n";
    std::cout<< "value at adr3 is "<<val1<< "\n";
    std::cout << "value at adr3+9 is "<<val2 << "\n";
}