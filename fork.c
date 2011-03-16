#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<fcntl.h>
#include<errno.h>
extern int errno;
int main(){
 char buf[100];
 pid_t cld_pid;
 int fd;
 int status;
 if((fd=open("temp",O_CREAT | O_TRUNC | O_RDWR ,S_IRWXU))==-1){
   printf("open error %d",errno);
   exit(1);
 }
 strcpy(buf,"This is parent process write");
 if((cld_pid=fork())==0){
   strcpy(buf,"This is child process write");
   printf("This is child process");
   printf("My PID(child) is %d",getpid());
   printf("My PID(parent) is %d",getpid());
   write(fd,buf,strlen(buf));
   close(fd);
   exit(0);
 }else{
  printf("This is parent process");
  printf("My PID(parent) is %d",getpid());
  printf("My PID(child) is %d",getpid());
  write(fd,buf,strlen(buf));
  close(fd);
 }
wait(&status);
}
