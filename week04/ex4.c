#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


int main ()
{

    char* argv[10];
    printf("welcome to SSHELL>>\n");


    while(1)
    {
        char cmd[10];


        scanf("%s", cmd);

        int wc = 0, cc = 0;

        argv[0] = cmd;
        
        if(fork() == 0)
        {
            execvp(argv[0], argv);
        }
    }
}