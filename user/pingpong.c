#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int 
main(int argc,char *argv[])
{
    if(argc!=1){
        fprintf(2,"Usage: pingpong...\n");
        exit(1);
    }
    int sign,p[2],current_pid,wait_sign=0;
    char buf[2];
    pipe(p); //create a pipe,put read/write file descriptors in p[0] and p[1].
    if(fork() != 0){ //parent
        for( ; ; ) {
            wait(0);
            sign = read(p[0],buf,1);
            if(sign < 0)
                fprintf(2,"read error...\n");
            else {
                current_pid = getpid();
                printf("%d: received pong",current_pid);
                close(p[0]);
                exit(0);
            } 
        }
    } else { //child
        write(p[1],"1",1);
        printf("%d: received ping",getpid());
        close(p[1]);
        exit(0);
    }
}