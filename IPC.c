/**
 *I read client
 *I write server 
 */
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
//#include <sys/stat.h>
#include <unistd.h>
#define SLEEPTIME 10

int main(int argc, char **argv)
{
  printf("executing");
 int i = 0;
 int pv = atoi(argv[1]); // paramater passed from php / cgi script (debating this still)
 int file_server, file_client;


 char str[256];
 char *buf;// character buffer ~ Stone Passed params 

 file_client = open("Kamikaze_Client",O_RDWR );
 file_server = open("Kamikaze_Server",O_RDWR);
 
 if((file_client <0)&&(file_server<0))
   {
     perror("aider of pipes open\n");
     exit(1);
}
 /*if(file_client < 0 ){
   printf("Error Kamikaze_Server Pipe not created\n please run the server");

   while(file_client<0){
     file_client = open("Kamikaze_Server",O_RDWR);
    sleep(SLEEPTIME); //just to slow execution and save some resource time 
    //printf("Testing the server problem error");
   }
 }else{
*/

 /**
  *Read from the client.
  *
  */
 
 buf = malloc(10*sizeof(char));

    read(file_client,buf,10*sizeof(char));
 char blank = ' ';
 close(file_client);
 write(file_server,&blank, 1);
 //FILE *file;
 // file = fopen("ran.txt","a+");
 //fprintf(file,"Content-Type: text/plain; charset=us-ascii\n\n");
 //fprintf(file, "<p> %s</p>",buf);
 //fclose(file);
 close(file_server);
 return 1;
 }

