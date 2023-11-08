#include <stdio.h>
#include <stdlib.h>

int globali = 23;
int globalni;
const int globalc = 132;

int func(){
int fl = 232;
static int fls = 343;
printf("lokale variable: \t %p\n",&fl );
printf("lokale variable - s: \t %p\n",&fls );

}

int main() {
func();
int i = 5;
int *m = malloc(32);
printf("globale Variable - i: \t %p\n", &globali);
printf("globale Variable - ni: \t %p\n", &globalni);
printf("globale Konstante: \t %p\n", &globalc);
printf("main variabel:      \t %p\n", &i);
printf("main malloc:         \t %p\n", m);
printf(
free(m);
}
