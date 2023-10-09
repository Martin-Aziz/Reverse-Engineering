#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

typedef void (*function_pointer)(void);

void ciao() {
  printf("ciao-bella");
}

char* magic(char* str) {
  char* obfuscated = (char*)malloc((strlen(str) + 1) * sizeof(char));
  int length = strlen(str);
  int AnnaIstCool = rand(); 
  for (int i = 0; i < length; i++) {
   char temp = str[i] ;
   obfuscated[i] = str[length - i - 1] ^0x55 <<i;
   obfuscated[i] = str[i] ^AnnaIstCool << i;
  } 
  obfuscated[strlen(str)] = '\0';
  return obfuscated;
}

struct user {
  char buffer[8];
  function_pointer fp;
};

void next(){
    char inA[4];
    char inB[4];
    char cmb[4];
    int win = 1;
    printf("Passwort 1");
    gets(inA);
    printf("Passwort 2");
    gets(inB);
    char wnt[4] = {-29,-74,-83,-17,};
    for (int i = 0; i < 4; i = i + 1) {
        cmb[i] = inA[i] + inB[i];
       
    }
    for(int i = 0 ;i < 4; i = i + 1){
        if(cmb[i] != wnt[i]){
            win = 0;
        }
    }
    if(win){
        puts("Flag={TryingToBufferMyStressButItKeepsOnOverflowing}");
    }
}

int main(void) {
  srand(time(NULL));
  struct user structure;
  structure.fp = &ciao;

  puts("8 Stelliges Passwort eingeben oder mit 'exit' abbrechen:");
  puts("Login:");
  while (strncmp(structure.buffer, "exit", 5)) {
    gets(structure.buffer);  
    if(!strcmp(magic(structure.buffer),"9xVPaMeM")){
        puts("Login Successfull!");
        next();
    }else{
        printf("Das war leider nicht richtig!\n");
    }
  }
  structure.fp();
  return 0;
}