#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(){

int file1, file2;
char c;

file1=open("text1",O_RDONLY);
file2=open("text2",O_WRONLY);

dup2(file2, 1);

while(read(file1, &c,sizeof(c))!=0){
write(1,&c,sizeof(c));}

}
