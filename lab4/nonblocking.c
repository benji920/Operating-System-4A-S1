#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <fcntl.h>
int main() {
int i; char
buf[100];
fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);
for (i = 0; i < 10; i++)
{ int nb;
nb = read(STDIN_FILENO, buf, 100);
printf("nwrites = %d\terror = %d\n", nb,
errno);
}
}