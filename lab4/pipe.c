#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
int main(int argc, char *argv[]) {
int pipefd[2];
pid_t cpid;
char buf;
if (pipe(pipefd) == -1) {
perror("pipe");
exit(EXIT_FAILURE);
}
cpid = fork(); if
(cpid == -1) {
perror("fork");
exit(EXIT_FAILURE);
}
if (cpid == 0) { /* Child reads from pipe */
close(pipefd[1]); /* Close unused write end */
dup2(pipefd[0],STDIN_FILENO); //make the standard input to be the read end
system("more"); //run more
close(pipefd[0]); // we close the read end
_exit(EXIT_SUCCESS);

} else { 
close(pipefd[0]); /* Close unused read end */
dup2(pipefd[1],STDOUT_FILENO);//make the standard output to be the write end
system("ps aux"); //run ps aux
close(pipefd[1]); //
wait(NULL);
/* Wait for child */
exit(EXIT_SUCCESS);
}
}
