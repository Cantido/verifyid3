#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define FAILURE -1
#define SUCCESS_MATCH 0
#define SUCCESS_NOMATCH 1

int main(int argc, char *argv[]){
  int return_code;
  
  int fd;
  unsigned char header[10];
  
  if(argc != 2){
    printf("Usage: %s filename", argv[0]);
    exit(FAILURE);
  }
  
  if((fd = open(argv[1], O_RDONLY)) < 0){
    perror(argv[0]);
    exit(FAILURE);
  }
  
  read(fd, header, 10);
  
  if( header[0] == 0x49 &&
      header[1] == 0x44 &&
      header[2] == 0x33 &&
      header[3] < 0xFF &&
      header[4] < 0xFF &&
      (header[5] & 0x3F) == 0x00 && /* sets first two bits to 0 */
      header[6] < 0x80 &&
      header[7] < 0x80 &&
      header[8] < 0x80 &&
      header[9] < 0x80){
    printf("%s has an ID3v2 tag!\n", argv[1]);
    return_code = SUCCESS_MATCH;
  }
  else{
    printf("%s does not have an ID3v2 tag.\n", argv[1]);
    return_code = SUCCESS_NOMATCH;
  }
  
  (void) close(fd);
  
  return return_code;
}
