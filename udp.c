#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char **argv)
{
  int sckid, lenPacket=atoi(argv[4]); 
  struct sockaddr_in servaddr; char packet[lenPacket]; 
  FILE *fp;
  
  sckid = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
  if(sckid<0){
    perror("socket creation failed");
    return(-1);
  }
  fp = fopen(argv[3], "r");
  if(fp==NULL)
  {
    printf("file name is not correct\n");
    return -1;
  }
  memset(&servaddr,0, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  inet_aton(argv[1], &servaddr.sin_addr);
  servaddr.sin_port = htons(atoi(argv[2])); 
  while(1)
  {        
    if((fread(packet, sizeof(packet), 1, fp))<=0)
      break;
    if(sendto(sckid,packet,lenPacket,0,(struct sockaddr*) &servaddr, (socklen_t) sizeof(servaddr))<0){
      perror("failed while sending");
      return(-1);
    }
    usleep(atoi(argv[5]));
  }
  return 0;
} 