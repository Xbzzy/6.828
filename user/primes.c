#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void
loop(int p[2])
{
    int p1[2],num,buf[1],sign=1;
    if(fork()==0){//child
        read(p[0],buf,1);
        sleep(1);
        write(p[1],&sign,1);
        num = buf[0];
        printf("prime %d",num);
        pipe(p1);
        loop(p1);
        while(0){
            int temp = read(p[0],buf,1);
            sleep(1);
            write(p[1],&sign,1);
            if(buf[0]%num != 0)
                write(p1[1],&buf[0],1);
            if(temp == 0){
                close(p1[1]); 
                exit(0);
            }
        }
    }
}
int 
main(int argc,char *argv[])
{
    if(argc!=1){//have argument
        fprintf(2,"Usage: primes...\n");
        exit(1);
    }
    int i,p[2],buf[1];
    pipe(p);//create a pipe,put read/write file descriptors in p[0] and p[1].
    loop(p);
    for(i=2;i<35;i++){
        write(p[1],&i,1);
        sleep(1);
        read(p[0],buf,1);
    }
    close(p[1]);
    close(p[0]);
    exit(0);
}