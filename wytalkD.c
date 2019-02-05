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
   else{
      printf("Connection established!\n");
   }
   // printf("wytalkD.c fd=%d\n", newsockfd);
   while(keepReading>0){
      printf("Inside the while loop.\n");
      char bufferRead[256];
      int rtnr;
      int rtnw;
      int run =1;
      // Next few lines are for the server to read the socket for input from client.
      while(run>0){
      printf("Reached the printing section.\n");
      //memset(bufferRead, 0, 256);
      rtnr = read(newsockfd, bufferRead, 255);
      printf("rtnr = %d\n", rtnr);
      if(rtnr<0){
         perror("read()");
         keepReading = -1;
         break;
      }else if(rtnr>0){
         printf("reached the printing part\n");
         printf("%s",bufferRead);
         //fflush(stdout);
         if (rtnr < 256){
            memset(bufferRead, 0, 256);
            run = -1;
         } 
      }
      else{
         run = -1;
      }
      }
      run = 1;
      // Next few lines are the code to write to the socket the input the server gives.
      // printf("Reached the part where it reads from stdin\n");
      if(keepReading>0){
         while(run>0){
         memset(bufferRead, 0, 256);
         // 255 here to prevent overflows.
         if((rtnr = read(0, bufferRead, 1)) < 0){
            perror("read() from stdin");
            keepReading = -1;
            break;
         }else if (rtnr > 0){
            printf("bufferRead = %s\n",bufferRead);
            rtnw = write(newsockfd, bufferRead, 1);
            if(rtnw < 0){
               perror("write() to socket.");
               keepReading = -1;
               break;
            }
            if(bufferRead[0] == '\n'){
               write(newsockfd, 0, 1);
               memset(bufferRead, 0, 256);
               printf("Reached the newline char\n");
               run = -1;
            }
         }
         //else{
           // run = -1;
         //}
         }
      }

      if(keepReading<0){
         printf("Seems like there is an error. Socket could possibly be closed by client.\n");
      }      
   }
   shutdown(sockfd, 2);
   shutdown(newsockfd, 2);
   close(sockfd);
   close(newsockfd);
   return 0;
}

