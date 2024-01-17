# Crackme Team 08

## Vorgehenweise

Um das crackme zu lösen schauen wir uns die passCheck Funktion an, die in der main aufgerufen wird.


## Lösungweg
```c
void passCheck(long param_1)

{
  char local_68 [84];
  int local_14;
  int *local_10;
  
  local_14 = 0;
  local_10 = &local_14;
  puts("You shall not pass! ");
  printf(*(char **)(param_1 + 8));
  printf("\nPsst, don\'t look: %p\n",secret);
  printf("Did you hear something?");
  gets(local_68);
  if (*local_10 != 0) {
    win();
  }
  return;
}
```
Zunächst wird ein char array local_68 wird mit 84 Bytes angeleget
Danach wird die die variable local_14 und der pointer local_10 angelegt.
local_10 zeigt auf den Inhalt von local_14.
in local_68 wird der user input gespeichert. da fgets benutzt wird, können wir einen buffer overflow nutzen um in local_14 zu schreiben.
Wenn wir einen Wert != 0 in local_14 schreiben wird die win() Funktion aufgerufen und die Flag ausgegeben

