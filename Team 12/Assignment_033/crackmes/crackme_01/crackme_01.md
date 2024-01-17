# Crackme Team 01

## Vorgehenweise

Um das crackme zu lösen schauen wir uns die validate Funktion an, die in der main aufgerufen wird.


## Lösungweg
```c
void validate(undefined8 param_1)

{
  undefined local_3b;
  undefined local_3a;
  undefined local_39;
  undefined local_38;
  char local_37 [25];
  undefined8 local_1e;
  undefined2 local_16;
  undefined local_14;
  undefined local_13;
  undefined local_12;
  undefined local_11;
  undefined4 local_10;
  int local_c;
  
  local_1e = 0x4f4e;
  local_16 = 0;
  printf("Enter the secret code: ");
  gets(local_37);
  local_c = atoi((char *)&local_1e);
  local_10 = fromGray(local_c);
  local_3b = (undefined)((uint)local_10 >> 0x18);
  local_3a = (undefined)((uint)local_10 >> 0x10);
  local_39 = (undefined)((uint)local_10 >> 8);
  local_38 = (undefined)local_10;
  local_14 = local_38;
  local_13 = local_39;
  local_12 = local_3a;
  local_11 = local_3b;
  xorHexPairs(param_1,&local_3b);
  return;
}
```
Wir können die gets Methode ausnutzen um einen Bufferoverflow zu erzeugen. Ab dem 26. Byte wird dann in 0x4f4e geschrieben. Der Aufruf von xorHexPairs weist darauf hin, dass der Schlüssel mit xor verschlüsselt ist. Der xorHexPairs Funktion wird der string aus der main sowie folgendes übergeben:
Das was mit dem Bufferoverflow in local_1e geschrieben wird, wird mit atoi in einen integer gecastet. Dieser Integer wird der fromGrey Methode übergeben und das Ergebnis um 24 Bits nach rechts geshiftet. Die fromGray Methode wandelt die Eingabe in den entsprechenden Binär Wert um.   

```c
void xorHexPairs(char *param_1,long param_2)

{
  size_t sVar1;
  uint local_20;
  char local_1b;
  char local_1a;
  undefined local_19;
  uint local_18;
  uint local_14;
  int local_10;
  int local_c;
  
  sVar1 = strlen(param_1);
  local_10 = (int)sVar1;
  if ((sVar1 & 1) == 0) {
    for (local_c = 0; local_c < local_10; local_c = local_c + 2) {
      local_1b = param_1[local_c];
      local_1a = param_1[(long)local_c + 1];
      local_19 = 0;
      __isoc99_sscanf(&local_1b,&DAT_00100bc8,&local_20);
      local_14 = (uint)*(char *)(param_2 + (local_c / 2) % 4);
      local_18 = local_20 ^ local_14;
      putchar(local_18);
    }
  }
  return;
}
```
local_14 = (uint)*(char *)(param_2 + (local_c / 2) % 4); Diese Zeile zeigt, dass der Schlüssel aus 4 chars besteht. Mit dem Wissen dass unser gesuchter String mit FLAG anfängt können wir den Rest ebenfalls entschlüsseln. Aus dem standard output ergibt sich dann der key "lotr". Da aber die greycodierte Version genutzt wird (wird durch fromGrey() wieder zurück umgewandelt) müssen wir lotr greycodieren: 

```c
uint toGray(uint param_1)

{
  return param_1 >> 1 ^ param_1;
}
```

Daraus ergibt sich: 1515769419

Dieser muss ab dem 26.Byte in der Eingabe angehängt werden. Dann erhält man das Flag.