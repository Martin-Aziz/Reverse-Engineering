# Musterlösung

## Schwachstelle
Buffer Overflow

Dem Executable wird als Argument oder Eingabe eine Menge an Chars übergeben sodass der Puffer überläuft.
Der Pointer der die Funktion anhand der gegebenen Speicheradresse aufruft speichert die Adresse in einer Variable. Diese Variable kann überschrieben werden beim Pufferüberlauf.
Dafür muss man wissen wo der Pufferüberlauf geschieht und was die Speicheradresse der gesuchten Funktion ist.

## Angriff
Overwriting a function pointer

1. Größe des Puffers herausfinden
2. Speicheradresse der Funktion herausfinden
3. Schwachstelle ausnutzen
