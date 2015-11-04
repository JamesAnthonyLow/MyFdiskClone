//must compile using -fpack-struct flag
#define _LARGEFILE64_SOURCE
#include "mbrParser.h"

unsigned char buff[512];

void printPartition(Partition * partition);

int main(int argc, char *argv[]) {
	int fd, bytesread;
  loff_t *result;
  Partition *mbrPartition;
  char * pathname = argv[1];

  MBR * mbrPtr = (MBR*)&buff[0];

	fd = open(pathname, O_RDWR);
	if(fd == -1)
		perror("Couldn't open!");
	bytesread = read(fd, buff, 512);

  int i = 0;
  while(mbrPtr->partition[i].u1.startSec != 0) {
      printf("%s%d/:\n", pathname, i+1);
      printPartition(&mbrPtr->partition[i]);
      i++;
  }

  printf("\n\n");
  unsigned long long int offset = 122897311;
  lseek64(fd, offset, SEEK_SET);
	bytesread = read(fd, buff, 512);
  if(bytesread != 512){
    perror("Couldn't read!");
  }

  i = 0;
  while(mbrPtr->partition[i].u1.startSec != 0) {
      printf("%s%d/:\n", pathname, i+1);
      printPartition(&mbrPtr->partition[i]);
      i++;
  }


	return 0;
}

void printPartition(Partition * partition){
  printf("Start\t\t\tEnd\t\t\tBlocks\t\tId\t\tSystem\n");
  int start = partition->u1.startSec;
  int end = partition->u2.partSize + partition->u1.startSec - 1;
  int id = partition->partitionType;
  printf("%d\t\t\t%d\t\t\t%d\n", start, end, id);
  //printf("\t\t%s\n\n", FS_TYPE[id]);
}
