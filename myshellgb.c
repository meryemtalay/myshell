/* 
Meryem Talay
meyremtlly@gmail.com
*/


#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h> // for pid structure
#include <unistd.h> // for fork and exec family
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>
#define BUFSIZE 100


int main(int argc, char *argv[]) {
// 
    char buf[250] = "/usr/bin/";
  
    int len = strlen(buf);
    int status;
// just print ">>" when the program is started (1)
    printf(">>");
      scanf("%100s", &buf[len]);
// started with fork();
  pid_t pid;
  pid = fork ();

  //child process
  if (pid == 0)
        { 
            int ret = -1;
            ret = execl(buf,"whereis", NULL);
            

            if (ret == -1)
            {
                printf("%s: command not found \n", buf);
                //while (1); //termination signal icin konuldu
                // When exec fails you should use _exit (or synonym _Exit) to cancel the subroutine
                exit(2);
            }

          int ret1=-1;
          ret1=execl(buf,"which",NULL);

          if(ret1==-1)
          {
            printf("%s: command not found \n", buf);
          }

          int ret2=-1;
          ret2=execl(buf,"command",NULL);

          if(ret2==-1){
             printf("%s: command not found \n", buf);
          }
           /*In CHILD PROCESS*/
int new_out = open("file", O_WRONLY | O_CREAT | O_TRUNC, 0666);
/*check for errors*/
 
/*dup() olarak DUZELTILDI
backup stdout, 1 den farkli bir deger stdoutu tutuyor*/
int saved_out = dup(1);
/*check for errors*/
 
close(1);/*file descriptor 1 empty*/
 
dup2(new_out, 1); /*duplicate new_out to 1*/
/*check for errors*/
 
/*exec...*/
 
/*tekrar stdoutu restore etme*/
dup2(saved_out, 1); /*duplicate saved_out to 1*/
 
close(saved_out);
close(new_out);
          }

  else if (pid > 0)
        {
          // -
          wait(&status);      
        }
  else 
  {
    perror("command not found");
  }
    
 
  return 0;
}
