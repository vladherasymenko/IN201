#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdint.h>
#include <stdio.h>

//Q2
struct fs_header {
	char rom1fs[8];
	char fullsize[4];
	uint32_t checksum;
	char volumename[];
} __attribute__((packed));

//Q4
uint32_t read32(char ptr[4]) {
	uint32_t res = ptr[0];
	res = res << 8;
	res = res | ptr[1];
	res = res << 8;
	res = res | ptr[2];
	res = res << 8;
	res = res | ptr[3];

	return res;
}

//Q5
int round16(int val) {
	int res = (val + 15) & (~0xf);
	return res;
}


void decode(struct fs_header *p, size_t size){
	//Q3
	printf("%s \n", p->rom1fs);

	//
	printf("Taille du fichier :  %zu\n", size);
	uint32_t fsize = read32(p->fullsize);
	printf("Fullsize : %lu\n", (unsigned long)fsize);

}

int main(void){

  int fd = open("tp1fs.romfs",O_RDONLY);
  assert(fd != -1);
  off_t fsize;
  fsize = lseek(fd,0,SEEK_END);

  //  printf("size is %d", fsize);
  
  void *addr = mmap(NULL, fsize, PROT_READ, MAP_SHARED, fd, 0);
  assert(addr != MAP_FAILED);
  decode(addr, fsize);
  return 0;
}
