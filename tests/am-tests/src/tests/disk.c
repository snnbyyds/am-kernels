#include <amtest.h>

#define DISK_CMD_READ  0
#define DISK_CMD_WRITE 1

static AM_DISK_CONFIG_T diskcfg;
static char testdata[4096];
static char testbuffer[1024];

static void inittestdata() {
  memset(testdata, 0, sizeof(testdata));
  strcpy(testdata, "blk1_somedummydata");
  strcpy(testdata + 512, "blk2_fhaskdhakjdhakjdhka");
  strcpy(testdata + 1024, "blk3_dakjshdkajhfkjashdkjahdkjsahfkjahskjfahkjahsdksadkjadkjashd");
}

void disk_test() {
  inittestdata();
  diskcfg = io_read(AM_DISK_CONFIG);
  if (!diskcfg.present) {
    printf("WARNING: %s does not support disk\n", TOSTRING(__ARCH__));
    return;
  }
  printf("Fetched disk config, blksz: %x, blkcnt: %d\n", diskcfg.blksz, diskcfg.blkcnt);
  printf("Start writing test with data: %s ...\n", testdata);
  io_write(AM_DISK_BLKIO, DISK_CMD_WRITE, testdata, 0, 4);
  printf("Start reading test...\n");
  io_write(AM_DISK_BLKIO, DISK_CMD_READ, testbuffer, 0, 2);
  printf("%d: %s\n", __LINE__, testbuffer);
  printf("%d: %s\n", __LINE__, testbuffer + diskcfg.blksz);
}
