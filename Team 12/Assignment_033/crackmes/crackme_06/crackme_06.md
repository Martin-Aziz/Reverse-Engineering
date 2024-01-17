# Crackme Team 06

## Vorgehenweise

Um das crackme zu lösen schauen wir uns die play Funktion an, die in der main aufgerufen wird.


## Lösungweg
```c
  for (local_2c = 0; local_2c < 6; local_2c = local_2c + 1) {
    for (local_24 = 0; local_24 < 6; local_24 = local_24 + 1) {
      if (local_16[local_2c] == *(byte *)((long)&eingabe + (long)local_24)) {
        local_28 = local_28 + 1;
      }
    }
  }
  if (local_28 == 6) {
    win();
  }
```
Wir sehen, dass die 6 richtigen Bytes, die in local_16 gespeichert sind mit den 6 Bytes aus der eingabe verglichen werden. Die verschachtelten for-Schleifen vergleichen jedoch jedes Byte 6 mal, das heißt es gibt insgesamt 36 vergleiche und daher muss nur ein Byte richtig sein. Wir können daher als input einfach 6 mal einen Punkt '.' eingeben, der chr(46) entspricht und müssen das ganze nur so oft wiederholen bis die richtige Lösung einen Punkt als Byte an einer beliebigen Stelle hat. Also wird '......' so oft eingegeben, bis die win() Funktion aufgerufen wird.
Dann erhalten wir das Flag.

