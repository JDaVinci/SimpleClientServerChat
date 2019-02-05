/*******************************
 * wytalkC.c
 * Krishna Sai Chemudupati
 * November 06, 2018
 * COSC 3750, Homework 7
 *
 * C source code for wytalkC (client version)
**********************************/

#include"socketfun.h"
#include<unistd.h>
#include<string.h>

int main(){
   char hostname[256];
   int port = 51100;
   int sockfd;
   int keepProcessing = 1;
   if(gethostname(hostname,256)<0){
     perror("gethostname()");
     return -1;
   }
   sockfd = request_connection(hostname, port);
   if(sockfd == -1 || sockfd == 1){
      perror("request_connection()");
      return -1;
   }
   else{
      printf("Connection established!\n");
   }
   //printf("wytalkC.c1 fd=%d\n", sockfd);
   while(keepProcessing >0){
      //printf("Inside the while loop.\n");
      char bufferRead[256];
      int rtnr;
      int rtnw;
      int run = 1;
      printf("Reached the reading from stdin part.\n");

      while(run>0){
         //memset(bufferRead, 0, 256);
         //rtnr = read(0, bufferRead, 255);
         //The next few lines of the code are for the client to enter input to be sent to the server.
         if((rtnr = read(0,bufferRead, 1)) < 0){
            perror("read() from stdin.");
            keepProcessing  = -1;
            break;
         }else if(rtnr > 0){ 
            printf("buffer Read=%s\n", bufferRead);
            // The next few lines are to write to the socket, for the server to read.
            rtnw = write(sockfd, bufferRead,1);
            if(rtnw <0){
               perror("write() to socket.");
               keepProcessing = -1;
               break;
            }
            if(bufferRead[0] == '\n'){
               write(sockfd, 0, 1);
               memset(bufferRead, 0, 256);
               printf("Reached the newline char.\n");
               run = -1;
            }
         }
         //else{
           // run =-1;
         //}
      }
      run = 1;
      // Here the next few lines are the code to read input from server and output.
      if(keepProcessing>0){
         printf("Reached the printing section.\n");
         while(run > 0){
         //memset(bufferRead, 0, 256);
         rtnr = read(sockfd, bufferRead, 255);
         printf("rtnr= %d\n", rtnr);
         // printf("wytalkC.c fd=%d\n", sockfd);
         if(rtnr <0){
            perror("read()");
            keepProcessing  = -1;
            break;
         }else if (rtnr>0){
            printf("Reached the printing part.\n");
            printf("%s", bufferRead);
            //fflush(stdout);
            if(rtnr < 256){
               memset(bufferRead, 0, 256);
               run = -1;
            }
         }
         else{
            run =-1;
         }
         }
      }
      if(keepProcessing <0){
         printf("Error! Socket could have been possibly closed by server.\n");
      } 
   }
   shutdown(sockfd, 2);
   close(sockfd);
   return 0;
}
