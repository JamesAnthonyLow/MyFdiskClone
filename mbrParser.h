#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

typedef struct {
  unsigned char bootIndicator;
  unsigned char startingCHS[3];
  unsigned char partitionType;
  unsigned char endingCHS[3];
  union {
    int startSec;
    unsigned char startingSector[4];
  } u1;
  union {
    int partSize;
  unsigned char partitionSize[4];
  } u2;
} Partition;

typedef struct {
  unsigned char bootCode[446];
  Partition partition[4];
  unsigned short bootSignature;
} MBR;

char * FS_TYPE[10]{"", 
               "DOS 12-bit FAT", 
               "XENIX root", 
               "XENIX/usr", 
               "DOS 3.0+ 16b FAT (<=32M)", 
               "DOS 3.3+ ext", 
               "DOS 3.31+ 16b FAT (>32M)", 
               "HPFS/NTFS/exFAT", 
               "AIX/SplitDrive/DELL (spanning)",
               "AIX data partition"};


