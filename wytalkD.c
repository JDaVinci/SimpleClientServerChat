/*******************************
 * wytalkD.c
 * Krishna Sai Chemudupati
 * November 06, 2018
 * COSC 3750, Homework 6
 *
 * C source code for wytalkD.c (server version)
**********************************/

#include"socketfun.h"
#include<unistd.h>
#include<string.h>

int main(){
   char hostname[256];
   int port = 51100;
   int sockfd;
   int newsockfd;
   int keepReading = 1;
   if(gethostname(hostname, 256)<0){
      perror("gethostname()");
      return -1;
   }
   printf("%s\n",hostname);   
   sockfd = serve_socket(hostname, port);
   if(sockfd  == -1 || sockfd == 1){
      perror("serve_socket()");
      return -1;
   }
   newsockfd = accept_connection(sockfd);
   if(newsockfd<0){
      perror("accept_connection()");
      return -1;
   }
   printf("wytalkD.c fd=%d\n", newsockfd);
   while(keepReading>0){
      printf("Inside the while loop.\n");
      char bufferRead[256];
      // memset(bufferRead, 0, 256);
      // char bufferWrite[256];
      int rtnr = 255;
      int rtnw;
      // rtnr initialised as -1.
     // while(rtnr == 255){
         memset(bufferRead, 0, 256);
         rtnr = read(newsockfd, bufferRead, 255);
         printf("rtnr = %d\n", rtnr);
         if(rtnr<0){
            perror("read()");
            keepReading = -1;
            break;
         }else if(rtnr>0){
            printf("reached the printing part\n");
            printf("%s\n",bufferRead); 
         }
     // }
      rtnr = -1;
      //while(rtnr != 0){
         printf("Reached the part where it reads from stdin\n");
         memset(bufferRead, 0, 256);
         // 255 here to prevent overflows.
         //rtnr = read(0,bufferRead, 255);
         //if(rtnr<0){
         if(fgets(bufferRead, 255, stdin) == NULL){
            perror("read() from stdin");
            keepReading = -1;
        //    break;
         }else{
            // if(rtnr>0){
            printf("bufferRead = %s\n",bufferRead);
            rtnw = write(newsockfd, bufferRead, strlen(bufferRead));
            if(rtnw < 0){
               perror("write() to socket.");
               keepReading = -1;
               //break;
            }
         }
      //}

      if(keepReading<0){
         printf("Seems like there is an error. Socket could possibly be closed by client.\n");
      }      
   }
   shutdown(sockfd, 2);
   shutdown(newsockfd, 2);
   return 0;
}

