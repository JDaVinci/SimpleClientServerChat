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
   int keepProcessing = -1;
   if(gethostname(hostname,256)<0){
     perror("gethostname()");
     return -1;
   }
   sockfd = request_connection(hostname, port);
   if(sockfd == -1 || sockfd == 1){
      perror("request_connection()");
      return -1;
   }
   //printf("wytalkC.c1 fd=%d\n", sockfd);
   while(keepProcessing <0){
      //printf("Inside the while loop.\n");
      char bufferRead[256];
      int rtnr = 255;
      int rtnw;
      //while(rtnr !=0){
      //while(rtnr == 255){
         /*memset(bufferRead, 0, 256);
         rtnr = read(sockfd, bufferRead, 255);
         printf("rtnr= %d\n", rtnr);
         printf("wytalkC.c fd=%d\n", sockfd);
         if(rtnr <0){
            perror("read()");
            keepProcessing  = -1;
          //  break;
         }else if (rtnr>0){
            printf("Reached the printing part.\n");
            printf("%s\n", bufferRead);
         }*/
      //}
      rtnr = -1;
      //while(rtnr !=0){
         printf("Reached the reading from stdin part.\n");
         memset(bufferRead, 0, 256);
         //rtnr = read(0, bufferRead, 255);
         //if(rtnr <0){
         if(fgets(bufferRead, 255, stdin) == NULL){
            perror("read() from stdin.");
            keepProcessing  = -1;
            // break;
         }else{ 
            //if (rtnr>0){
            printf("buffer Read=%s\n", bufferRead);
            rtnw = write(sockfd, bufferRead, strlen(bufferRead));
            if(rtnw <0){
               perror("write() to socket.");
               keepProcessing = -1;
               // break;
            }
         }
      //}
         memset(bufferRead, 0, 256);
         rtnr = read(sockfd, bufferRead, 255);
         printf("rtnr= %d\n", rtnr);
         printf("wytalkC.c fd=%d\n", sockfd);
         if(rtnr <0){
            perror("read()");
            keepProcessing  = -1;
          //  break;
         }else if (rtnr>0){
            printf("Reached the printing part.\n");
            printf("%s\n", bufferRead);
         }

      if(keepProcessing <0){
         printf("Error! Socket could have been possibly closed by server.\n");
      } 
   }
   shutdown(sockfd, 2);
   return 0;
}
